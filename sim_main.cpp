#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include <atomic>
//#include <fstream>

#include <verilated.h>
#include "Vgba_top.h"


#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>

#include "imgui_memory_editor.h"


// DirectX data
static ID3D11Device*            g_pd3dDevice = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
static IDXGIFactory*            g_pFactory = NULL;
static ID3D11Buffer*            g_pVB = NULL;
static ID3D11Buffer*            g_pIB = NULL;
static ID3D10Blob*              g_pVertexShaderBlob = NULL;
static ID3D11VertexShader*      g_pVertexShader = NULL;
static ID3D11InputLayout*       g_pInputLayout = NULL;
static ID3D11Buffer*            g_pVertexConstantBuffer = NULL;
static ID3D10Blob*              g_pPixelShaderBlob = NULL;
static ID3D11PixelShader*       g_pPixelShader = NULL;
static ID3D11SamplerState*      g_pFontSampler = NULL;
static ID3D11ShaderResourceView*g_pFontTextureView = NULL;
static ID3D11RasterizerState*   g_pRasterizerState = NULL;
static ID3D11BlendState*        g_pBlendState = NULL;
static ID3D11DepthStencilState* g_pDepthStencilState = NULL;
static int                      g_VertexBufferSize = 5000, g_IndexBufferSize = 10000;


// Instantiation of module.
Vgba_top* top = new Vgba_top;

char my_string[400];
int str_i = 0;

unsigned int row;
unsigned int col;
unsigned int bank;
unsigned int dram_address;

int pix_count = 0;

unsigned char rgb[3];
bool prev_vsync = 0;
int frame_count = 0;

bool vga_file_select = 0;

bool prev_hsync = 0;
int line_count = 0;

bool prev_sram_we_n = 0;

uint32_t inst_data_temp;

uint32_t prev_pc = 0xDEADBEEF;

unsigned int avm_byte_addr;
unsigned int avm_word_addr;

unsigned int burstcount;
unsigned int byteenable;
unsigned int writedata;

unsigned int datamux;	// What the aoR3000 core is actually reading from the bus! Only valid when avm_readdata_valid is High!
unsigned int datatemp;

unsigned int old_pc;
unsigned int inst_count = 0;

unsigned int old_hw_addr;
unsigned int hw_count = 0;

bool trigger1 = 0;
bool trigger2 = 0;

int trig_count = 0;

uint16_t byteena_bits;

bool ram_read_flag = 0;
bool ram_write_flag = 0;

FILE *vgap;

int last_sdram_writedata = 0;
int last_sdram_byteaddr = 0;
int last_sdram_ben = 0;

bool run_enable = 0;
bool single_step = 0;
bool multi_step = 0;
int multi_step_amount = 1024;


// Data
static IDXGISwapChain*          g_pSwapChain = NULL;
static ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;

void CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();
}

void CleanupRenderTarget()
{
	if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

HRESULT CreateDeviceD3D(HWND hWnd)
{
	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
		return E_FAIL;

	CreateRenderTarget();

	return S_OK;
}

void CleanupDeviceD3D()
{
	CleanupRenderTarget();
	if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
	if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			CleanupRenderTarget();
			g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

static float values[90] = { 0 };
static int values_offset = 0;





vluint64_t main_time = 0;	// Current simulation time.

unsigned int file_size;

unsigned char buffer[16];

unsigned int bios_size = 1024 * 256 * 4;		// 1MB. (32-bit wide).
uint32_t *bios_ptr = (uint32_t *) malloc(bios_size);

unsigned int cart_size = 1024 * 1024 * 4;		// 16MB. (32-bit wide).
uint32_t *cart_ptr = (uint32_t *)malloc(cart_size);

/*
unsigned int exp_size = 1024 * 1024 * 4;	// 1MB. (32-bit wide).
uint32_t *exp_ptr = (uint32_t *)malloc(exp_size);
*/

unsigned int ram_size = 1024 * 512 * 4;		// 2MB. (32-bit wide).
uint32_t *ram_ptr = (uint32_t *) malloc(ram_size);

unsigned int vram_size = 1024 * 1024 * 4;	// 4MB. (32-bit wide).
uint32_t *vram_ptr = (uint32_t *) malloc(vram_size);

unsigned int disp_size = 1024 * 1024 * 4;	// 4MB. (32-bit wide).
uint32_t *disp_ptr = (uint32_t *)malloc(disp_size);

uint32_t vga_size  = 1024 * 1024 * 4;		// 4MB. (32-bit wide).
uint32_t *vga_ptr  = (uint32_t *) malloc(vga_size);

uint32_t exe_size = 1024 * 512 * 4;			// 2MB. (32-bit wide).
uint32_t *exe_ptr = (uint32_t *) malloc(exe_size);

uint32_t first_cmd_word = 0;

/*
unsigned int ram_size0 = 1024*1024*8;	// 32MB. (32-bit wide).
uint32_t *bank0_ptr = (uint32_t *) malloc(ram_size0);
*/

uint8_t clk_cnt = 0;


double sc_time_stamp () {	// Called by $time in Verilog.
	return main_time;
}


/*
void get_opcode_string(uint32_t inst) {

	uint32_t opcode			= (inst&0xFC000000)>>26;
	uint32_t rs				= (inst&0x03E00000)>>21;
	uint32_t rt				= (inst&0x001F0000)>>16;
	uint32_t rd				= (inst&0x0000F800)>>11;
	uint32_t funct			= (inst&0x0000003F)>>0;
	uint32_t immediate		= (inst&0x0000FFFF)>>0;
	uint32_t jumpaddress	= (inst&0x03FFFFFF)>>0;
	uint32_t cp0_sel		= (inst&0x00000007)>>0;


uint8_t Funct_Add     = 0b100000;
parameter [5:0] Funct_Addu    = 0b100001;
parameter [5:0] Funct_And     = 0b100100;
parameter [5:0] Funct_Break   = 0b001101;
parameter [5:0] Funct_Clo     = 0b100001; // same as Addu
parameter [5:0] Funct_Clz     = 0b100000; // same as Add
parameter [5:0] Funct_Div     = 0b011010;
parameter [5:0] Funct_Divu    = 0b011011;
parameter [5:0] Funct_Jr      = 0b001000;
parameter [5:0] Funct_Jalr    = 0b001001;
parameter [5:0] Funct_Madd    = 0b000000;
parameter [5:0] Funct_Maddu   = 0b000001;
parameter [5:0] Funct_Mfhi    = 0b010000;
parameter [5:0] Funct_Mflo    = 0b010010;
parameter [5:0] Funct_Movn    = 0b001011;
parameter [5:0] Funct_Movz    = 0b001010;
parameter [5:0] Funct_Msub    = 0b000100; // same as Sllv
parameter [5:0] Funct_Msubu   = 0b000101;
parameter [5:0] Funct_Mthi    = 0b010001;
parameter [5:0] Funct_Mtlo    = 0b010011;
parameter [5:0] Funct_Mul     = 0b000010; // same as Srl
parameter [5:0] Funct_Mult    = 0b011000;
parameter [5:0] Funct_Multu   = 0b011001;
parameter [5:0] Funct_Nor     = 0b100111;
parameter [5:0] Funct_Or      = 0b100101;
parameter [5:0] Funct_Sll     = 0b000000;
parameter [5:0] Funct_Sllv    = 0b000100;
parameter [5:0] Funct_Slt     = 0b101010;
parameter [5:0] Funct_Sltu    = 0b101011;
parameter [5:0] Funct_Sra     = 0b000011;
parameter [5:0] Funct_Srav    = 0b000111;
parameter [5:0] Funct_Srl     = 0b000010;
parameter [5:0] Funct_Srlv    = 0b000110;
parameter [5:0] Funct_Sub     = 0b100010;
parameter [5:0] Funct_Subu    = 0b100011;
parameter [5:0] Funct_Syscall = 0b001100;
parameter [5:0] Funct_Teq     = 0b110100;
parameter [5:0] Funct_Tge     = 0b110000;
parameter [5:0] Funct_Tgeu    = 0b110001;
parameter [5:0] Funct_Tlt     = 0b110010;
parameter [5:0] Funct_Tltu    = 0b110011;
parameter [5:0] Funct_Tne     = 0b110110;
parameter [5:0] Funct_Xor     = 0b100110;

            case (OpCode)
                // R-Type
                Op_Type_R  :
                    begin
                        case (Funct)
                            Funct_Add     : Datapath <= DP_Add;
                            Funct_Addu    : Datapath <= DP_Addu;
                            Funct_And     : Datapath <= DP_And;
                            Funct_Break   : Datapath <= DP_Break;
                            Funct_Div     : Datapath <= DP_Div;
                            Funct_Divu    : Datapath <= DP_Divu;
                            Funct_Jalr    : Datapath <= DP_Jalr;
                            Funct_Jr      : Datapath <= DP_Jr;
                            Funct_Mfhi    : Datapath <= DP_Mfhi;
                            Funct_Mflo    : Datapath <= DP_Mflo;
                            Funct_Movn    : Datapath <= DP_Movn;
                            Funct_Movz    : Datapath <= DP_Movz;
                            Funct_Mthi    : Datapath <= DP_Mthi;
                            Funct_Mtlo    : Datapath <= DP_Mtlo;
                            Funct_Mult    : Datapath <= DP_Mult;
                            Funct_Multu   : Datapath <= DP_Multu;
                            Funct_Nor     : Datapath <= DP_Nor;
                            Funct_Or      : Datapath <= DP_Or;
                            Funct_Sll     : Datapath <= DP_Sll;
                            Funct_Sllv    : Datapath <= DP_Sllv;
                            Funct_Slt     : Datapath <= DP_Slt;
                            Funct_Sltu    : Datapath <= DP_Sltu;
                            Funct_Sra     : Datapath <= DP_Sra;
                            Funct_Srav    : Datapath <= DP_Srav;
                            Funct_Srl     : Datapath <= DP_Srl;
                            Funct_Srlv    : Datapath <= DP_Srlv;
                            Funct_Sub     : Datapath <= DP_Sub;
                            Funct_Subu    : Datapath <= DP_Subu;
                            Funct_Syscall : Datapath <= DP_Syscall;
                            Funct_Teq     : Datapath <= DP_Teq;
                            Funct_Tge     : Datapath <= DP_Tge;
                            Funct_Tgeu    : Datapath <= DP_Tgeu;
                            Funct_Tlt     : Datapath <= DP_Tlt;
                            Funct_Tltu    : Datapath <= DP_Tltu;
                            Funct_Tne     : Datapath <= DP_Tne;
                            Funct_Xor     : Datapath <= DP_Xor;
                            default       : Datapath <= DP_None;
                        endcase
                    end
                // R2-Type
                Op_Type_R2 :
                    begin
                        case (Funct)
                            Funct_Clo   : Datapath <= DP_Clo;
                            Funct_Clz   : Datapath <= DP_Clz;
                            Funct_Madd  : Datapath <= DP_Madd;
                            Funct_Maddu : Datapath <= DP_Maddu;
                            Funct_Msub  : Datapath <= DP_Msub;
                            Funct_Msubu : Datapath <= DP_Msubu;
                            Funct_Mul   : Datapath <= DP_Mul;
                            default     : Datapath <= DP_None;
                        endcase
                    end
                // I-Type
                Op_Addi    : Datapath <= DP_Addi;
                Op_Addiu   : Datapath <= DP_Addiu;
                Op_Andi    : Datapath <= DP_Andi;
                Op_Ori     : Datapath <= DP_Ori;
                Op_Pref    : Datapath <= DP_Pref;
                Op_Slti    : Datapath <= DP_Slti;
                Op_Sltiu   : Datapath <= DP_Sltiu;
                Op_Xori    : Datapath <= DP_Xori;
                // Jumps (using immediates)
                Op_J       : Datapath <= DP_J;
                Op_Jal     : Datapath <= DP_Jal;
                // Branches and Traps
                Op_Type_BI :
                    begin
                        case (Rt)
                            OpRt_Bgez   : Datapath <= DP_Bgez;
                            OpRt_Bgezal : Datapath <= DP_Bgezal;
                            OpRt_Bltz   : Datapath <= DP_Bltz;
                            OpRt_Bltzal : Datapath <= DP_Bltzal;
                            OpRt_Teqi   : Datapath <= DP_Teqi;
                            OpRt_Tgei   : Datapath <= DP_Tgei;
                            OpRt_Tgeiu  : Datapath <= DP_Tgeiu;
                            OpRt_Tlti   : Datapath <= DP_Tlti;
                            OpRt_Tltiu  : Datapath <= DP_Tltiu;
                            OpRt_Tnei   : Datapath <= DP_Tnei;
                            default     : Datapath <= DP_None;
                        endcase
                    end                         
                Op_Beq     : Datapath <= DP_Beq;
                Op_Bgtz    : Datapath <= DP_Bgtz;
                Op_Blez    : Datapath <= DP_Blez;
                Op_Bne     : Datapath <= DP_Bne;
                // Coprocessor 0
                Op_Type_CP0 :
                    begin
                        case (Rs)
                            OpRs_MF   : Datapath <= DP_Mfc0;
                            OpRs_MT   : Datapath <= DP_Mtc0;
                            OpRs_ERET : Datapath <= (Funct == Funct_ERET) ? DP_Eret : DP_None;
                            default   : Datapath <= DP_None;
                        endcase
                    end
                // Coprocessor 2
                Op_Type_CP2 :
                    begin
                        case (Rs)
                            OpRs_CF   : Datapath <= DP_Cfc2;
                            OpRs_CT   : Datapath <= DP_Ctc2;
                            OpRs_MF   : Datapath <= DP_Mfc2;
                            OpRs_MT   : Datapath <= DP_Mtc2;
                            default   : Datapath <= DP_None;
                        endcase
                    end
                // Memory
                Op_Lb   : Datapath <= DP_Lb;
                Op_Lbu  : Datapath <= DP_Lbu;
                Op_Lh   : Datapath <= DP_Lh;
                Op_Lhu  : Datapath <= DP_Lhu;
                Op_Ll   : Datapath <= DP_Ll;
                Op_Lui  : Datapath <= DP_Lui;
                Op_Lw   : Datapath <= DP_Lw;
                Op_Lwc2 : Datapath <= DP_Lwc2;
                Op_Lwl  : Datapath <= DP_Lwl;
                Op_Lwr  : Datapath <= DP_Lwr;
                Op_Sb   : Datapath <= DP_Sb;
                Op_Sc   : Datapath <= DP_Sc;
                Op_Sh   : Datapath <= DP_Sh;
                Op_Sw   : Datapath <= DP_Sw;
                Op_Swc2 : Datapath <= DP_Swc2;
                Op_Swl  : Datapath <= DP_Swl;
                Op_Swr  : Datapath <= DP_Swr;
                default : Datapath <= DP_None;
            endcase
);
*/

int verilate() {
	if (!Verilated::gotFinish()) {
		//while ( top->FL_ADDR < 0x0100 ) {		// Only run for a short time.
		if (main_time < 8) {
			top->reset = 1;   	// Assert reset (active HIGH)
		}
		if (main_time == 8) {	// Do == here, so we can still reset it in the main loop.
			top->reset = 0;		// Deassert reset.
		}
		if ((main_time & 1) == 0) {
			top->gba_clk = 0;       // Toggle clock
			top->clk_100 = 0;
			top->clk_256 = 0;
			top->vga_clk = 0;				
		}
		if ((main_time & 1) == 1) {
			top->gba_clk = 1;
			top->clk_100 = 1;
			top->clk_256 = 1;
			top->vga_clk = 1;

			if (top->bus_system_read && top->bus_mem_addr>>2 < bios_size)  {
				/*if (top->bus_mem_addr>>2==0x0260>>2 || top->bus_mem_addr>>2==0x0310>>2) top->bus_system_rdata = 0x00000000;	// NOP out some BNEs, which are used loop which clear SDRAM. Help speed up the sim!
				else*/
					top->bus_system_rdata = bios_ptr[top->bus_mem_addr>>2];	// Read Flash data from our loaded BIOS ROM file.

				// Byteswap! (32-bit)
				//uint32_t bios_word = bios_ptr[top->bus_mem_addr >> 2];
				//top->bus_system_rdata = (bios_word & 0xFF000000) >> 24 | (bios_word & 0x00FF0000) >> 8 | (bios_word & 0x0000FF00) << 8 | (bios_word & 0x000000FF) << 24;

				// Byteswap! (16-bit)
				//uint32_t bios_word = bios_ptr[top->bus_mem_addr >> 2];
				//top->bus_system_rdata = (bios_word & 0xFF000000) >> 8 | (bios_word & 0x00FF0000) << 8 | (bios_word & 0x0000FF00) >> 8 | (bios_word & 0x000000FF) << 8;
			}
			/*
			else if (top->in_PPORT && top->bus_mem_addr < bios_size) {
				top->bus_system_rdata = exp_ptr[top->bus_mem_addr];
				//top->bus_system_rdata = exp_ptr[top->bus_mem_addr>>2];
				//top->bus_system_rdata = (top->bus_system_rdata & 0xFF000000) >> 8 | (top->bus_system_rdata & 0x00FF0000) << 8 | (top->bus_system_rdata & 0x0000FF00) >> 8 | (top->bus_system_rdata & 0x000000FF) << 8;

				printf("Expansion ROM read, from 0x%08X, data=0x%08X\n", top->bus_mem_addr>>2, top->bus_system_rdata);

				//run_enable = 0;
			}
			*/

			if (top->bus_mem_addr >= 0x02000000 && top->bus_mem_addr <= 0x03FFFFFF && top->gba_top__DOT__bus_write) {
				ram_ptr[(top->bus_mem_addr&0x00FFFFFF) >> 2] = top->gba_top__DOT__bus_wdata;
			}

			if (top->bus_game_read && top->bus_mem_addr >> 2 < cart_size) {
				/*if (top->bus_mem_addr>>2==0x0260>>2 || top->bus_mem_addr>>2==0x0310>>2) top->bus_system_rdata = 0x00000000;	// NOP out some BNEs, which are used loop which clear SDRAM. Help speed up the sim!
				else*/ top->bus_game_rdata = cart_ptr[top->bus_mem_addr >> 2];	// Read Flash data from our loaded BIOS ROM file.
			}

			//printf("bus_mem_addr>>2: %08X  bus_system_rdata: %08X\n", top->bus_mem_addr>>2<<2, top->bus_system_rdata);

			//if (old_pc != top->pc) printf("pc: %08X  inst_read: %d  mdr: %d  mem_addr: %08X  inst: %08X  mem_data_in: %08X  mem_data_out: %08X\n", top->pc<<2, top->inst_read, top->mem_data_read, top->bus_mem_addr<<2, top->inst, top->mem_data_in, top->mem_data_out);

			// This code MUST go BEFORE the SDRAM READ code below!
			// The PSX core needs to see sd_valid go Low before it will continue the read.
			// We check ram_read_flag here, then set sd_valid High only after the NEXT tick of CLOCK_50.
			/*
			if (ram_read_flag == 1) {
				ram_read_flag = 0;
				top->sd_valid = 1;
				top->sd_waitrequest = 0;
			}

			if (ram_write_flag == 1) {
				ram_write_flag = 0;
				top->sd_waitrequest = 0;
			}

			if (top->sd_wen) {
				//if ( top->pc == 0x80059DE0 >> 2 ) ram_ptr[0x001FFD2E >> 2] = 0x0001;	// Cancel out the annoying delay loop.

				if (top->data_ben & 8) ram_ptr[top->sd_addr] = (ram_ptr[top->sd_addr] & 0x00FFFFFF) | (top->sd_data_i & 0xFF000000);
				if (top->data_ben & 4) ram_ptr[top->sd_addr] = (ram_ptr[top->sd_addr] & 0xFF00FFFF) | (top->sd_data_i & 0x00FF0000);
				if (top->data_ben & 2) ram_ptr[top->sd_addr] = (ram_ptr[top->sd_addr] & 0xFFFF00FF) | (top->sd_data_i & 0x0000FF00);
				if (top->data_ben & 1) ram_ptr[top->sd_addr] = (ram_ptr[top->sd_addr] & 0xFFFFFF00) | (top->sd_data_i & 0x000000FF);

				top->sd_waitrequest = 1;
				ram_write_flag = 1;
				//printf("SDRAM WRITE. sd_addr: %08X  byte_addr: %08X  data_from_core: %08X  data_ben: %01X\n", top->sd_addr, top->sd_addr<<2, top->sd_data_i, top->data_ben);	//  Note sd_data_i is OUT of the sim!

				last_sdram_writedata = top->sd_data_i;
				last_sdram_byteaddr  = top->sd_addr << 2;
				last_sdram_ben       = top->data_ben;

				if (top->sd_addr == 0x0006EE0) {
					printf("SDRAM WRITE. sd_addr: %08X  byte_addr: %08X  data_from_core: %08X  data_ben: %01X\n", top->sd_addr, top->sd_addr << 2, top->sd_data_i, top->data_ben);	//  Note sd_data_i is OUT of the sim!
					printf("data read back from SDRAM: %08X\n", bios_ptr[top->bus_mem_addr>>2]);
				}
			}

			if (top->sd_ren) {
				if (top->sd_addr == 0x00002834 >> 2	// NOP out the Kernel IO debug thingy routine (SCPH1001 BIOS. Normally has a jal $00002870 there).
					|| top->sd_addr == 0x0005418C >> 2	// NOP out an SPU init routine (SCPH1001 BIOS).
					|| top->sd_addr == 0x000545C8 >> 2 	// NOP out some SPU sample transfer stuff (SCPH1001 BIOS).
					top->sd_data_o = 0x00000000;	// The NOP itself. (SDRAM access is 32-bit wide on the core, btw!)
				else top->sd_data_o = ram_ptr[top->sd_addr];	// Else, normal read from SDRAM.
				top->sd_valid = 0;
				ram_read_flag = 1;
				//printf("SDRAM READ.  sd_addr: %08X  sd_data_in: %08X  sd_valid: %d  sd_wait: %d  state: %d  next_state: %d  ack: %d  next_ack: %d\n", top->sd_addr, top->sd_data_o, top->sd_valid, top->sd_waitrequest, top->addr_curr_state, top->addr_next_state, top->addr_curr_ack, top->addr_next_ack);	//  Note sd_data_o is IN to the sim!
			}
			*/

			/*
			if (top->pc == 0x000005F4>>2) {
				char my_byte;
				my_byte = top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[4];

				printf("my_byte %s\n", my_byte);

				if (my_byte == 0x0A) {
					for (int i = 0; i < str_i; i++) {
						printf("%s", my_string[i]);
					}
					printf("\n");
					str_i = 0;
				}
				else my_string[str_i] = my_byte;
				
				if (str_i < 400) str_i++;
			}
			*/

			//printf("ID_Cfc2: %d, ID_Ctc2: %d, ID_Mfc2: %d, ID_Mtc2: %d, ID_Lwc2: %d, ID_Swc2: %d ID_Mfc0: %d, ID_Mtc0: %d, ID_Eret: %d\n", top->ID_Cfc2, top->ID_Ctc2, top->ID_Mfc2, top->ID_Mtc2, top->ID_Lwc2, top->ID_Swc2, top->ID_Mfc0, top->ID_Mtc0, top->ID_Eret);


			/*
			if (old_pc == top->pc) {
				if (inst_count < 10000) inst_count++;
				else {
					//printf("Stuck on instruction: %08X  bus_mem_addr: %08X  pc: %08X  sd_addr: %08X\n", top->inst, top->bus_mem_addr<<2, top->pc<<2, top->sd_addr);

					
					uint32_t opcode = (top->inst & 0xFC000000) >> 26;
					uint32_t rs = (top->inst & 0x03E00000) >> 21;
					uint32_t rt = (top->inst & 0x001F0000) >> 16;
					uint32_t rd = (top->inst & 0x0000F800) >> 11;
					uint32_t funct = (top->inst & 0x0000003F) >> 0;
					uint32_t immediate = (top->inst & 0x0000FFFF) >> 0;
					uint32_t jumpaddress = (top->inst & 0x03FFFFFF) >> 0;
					uint32_t cp0_sel = (top->inst & 0x00000007) >> 0;
					
					//printf("Stuck at pc: %08X  addr: %08X  inst: %08X  opc: %02x  rs: %02x  rt: %02x  rd: %02x  func: %02x  imm: %04x  jumpadr: %08X  cp0: %01x\n", top->pc << 2, top->bus_mem_addr, top->inst, opcode, rs, rt, rd, funct, immediate, jumpaddress, cp0_sel);

					//printf("Stuck at pc: %08X  addr: %08X  inst: %08X\n", top->pc << 2, top->bus_mem_addr, top->inst);

					//printf("IF_S %d, IFE_S: %d,  ID_S: %d,  ID_E: %d,  EX_ALU_S: %d,  EX_S: %d,  EX_E_S: %d,  M_S: %d,  M_S_Cont: %d,  M_E_S: %d,  WB_S:  %d  IP: %02X\n", top->IF_Stall, top->IF_Exception_Stall, top->ID_Stall, top->ID_Exception_Stall, top->EX_ALU_Stall, top->EX_Stall, top->EX_Exception_Stall, top->M_Stall, top->M_Stall_Controller, top->M_Exception_Stall, top->WB_Stall, top->IP);

					//printf("ID_Cfc2: %d, ID_Ctc2: %d, ID_Mfc2: %d, ID_Mtc2: %d, ID_Lwc2: %d, ID_Swc2: %d ID_Mfc0: %d, ID_Mtc0: %d, ID_Eret: %d\n", top->ID_Cfc2, top->ID_Ctc2, top->ID_Mfc2, top->ID_Mtc2, top->ID_Lwc2, top->ID_Swc2, top->ID_Mfc0, top->ID_Mtc0, top->ID_Eret);

					//printf("bus_system_read: %d, in_MAIN: %d, in_PPORT: %d, in_SCPAD: %d, bus_io_reg_read: %d\n", top->bus_system_read, top->in_MAIN, top->in_PPORT, top->in_SCPAD, top->bus_io_reg_read);

					printf("GPUBUS: %08X  GPUREAD: %08X  GPUSTAT: %08X\n", top->gpu_main_bus, top->gpu_read, top->gpu_stat);
					inst_count = 0;
				}
			}
			else {
				inst_count = 0;
				//printf("addr: %08X  inst: %08X\n", top->bus_mem_addr, top->inst);
			}
			*/

			/*
			if (top->service_DMA) {
				printf("service_DMA: %d  dma_addr: %08X  dma_ren: %d  dma_wen: %d  dma_req: %d  dma_done: %d  ack_o: %d\n", top->service_DMA, top->dma_addr, top->dma_ren, top->dma_wen, top->dma_req, top->dma_done, top->ack_o);
				run_enable = 0;
			}
			*/

			//if (top->halted) printf("CPU Halted!\n");

			//if (top->pc==0x80051050>>2) trigger1 = 1;
			/*
			if (top->pc == 0x8005a4c4 >> 2) trigger1 = 1;
			if (trigger1) {
				if (top->pc != old_pc) {
					printf("pc: %08X  bus_mem_addr: %08X   mem_addr: %08X  inst: %08X  mem_data_in: %08X  mem_data_out: %08X  GPUBUS: %08X  GPUREAD_1810: %08X  GPUSTAT_1814: %08X  gpu_fifo_full: %d\n", top->pc << 2, top->bus_mem_addr, top->bus_mem_addr, top->inst, top->mem_data_in, top->mem_data_out, top->gpu_main_bus, top->gpu_read, top->gpu_stat, top->gpu_fifo_full);

					printf("service_DMA: %d  dma_addr: %08X  dma_ren: %d  dma_wen: %d  dma_req: %d  dma_done: %d  ack_o: %d\n", top->service_DMA, top->dma_addr<<2, top->dma_ren, top->dma_wen, top->dma_req, top->dma_done, top->ack_o);

					//printf("Stall flags: IF:%d IFE:%d ID:%d IDE:%d EX_ALU:%d EX:%d EXE:%d MS:%d MSC:%d ME:%d WB:%d\n", top->IF_Stall, top->IF_Exception_Stall, top->ID_Stall, top->ID_Exception_Stall, top->EX_ALU_Stall, top->EX_Stall, top->EX_Exception_Stall, top->M_Stall, top->M_Stall_Controller, top->M_Exception_Stall, top->WB_Stall);

					//printf("ID: CFC2:%d CTC2:%d MFC:%d MTC:%d LWC2:%d SWC2:%d MFC0:%d MTC0:%d ERET:%d\n", top->ID_Cfc2, top->ID_Ctc2, top->ID_Mfc2, top->ID_Mtc2, top->ID_Lwc2, top->ID_Swc2, top->ID_Mfc0, top->ID_Mtc0, top->ID_Eret);

					//printf("Addr CS flags: BIOS:%d  MAIN:%d  PPORT:%d  SCPAD:%d  HWREG:%d\n", top->bus_system_read, top->in_MAIN, top->in_PPORT, top->in_SCPAD, top->bus_io_reg_read);

					trig_count++;
				}
				//if (trig_count==2000) exit(0);
				if (frame_count == 50) exit(0);
			}
			*/

			
			old_pc = top->gba_top__DOT__cpu__DOT__cpu__DOT__RegFile_PCOut;

			if (top->bus_io_reg_read /*&& top->bus_mem_addr != old_hw_addr*/) {
				unsigned int my_data;
				
				if (top->gba_top__DOT__cpu__DOT__cpu__DOT__WRITE) {
					printf("WRITE to IO  0x%08X  ", top->bus_mem_addr);
					my_data = top->gba_top__DOT__cpu__DOT__cpu__DOT__WDATA;

				}
				else {
					printf("READ from IO 0x%08X  ", top->bus_mem_addr);
					my_data = top->gba_top__DOT__cpu__DOT__cpu__DOT__RDATA;
				}
				
				switch (top->bus_mem_addr) {
					case 0x04000208: printf("IME:     (PC=0x%08X) (data=0x%08X)\n", top->gba_top__DOT__cpu__DOT__cpu__DOT__RegFile_PCOut, my_data); break;
					case 0x04000300: printf("POSTFLG: (PC=0x%08X) (data=0x%08X)\n", top->gba_top__DOT__cpu__DOT__cpu__DOT__RegFile_PCOut, my_data); break;

					default:         printf("         (PC=0x%08X) (data=0x%08X)\n", top->gba_top__DOT__cpu__DOT__cpu__DOT__RegFile_PCOut, my_data); break;
				}

				printf("bus_addr_lat1=0x%08X\n", top->gba_top__DOT__mem__DOT__bus_addr_lat1);
			}

			//if (top->bus_io_reg_read) old_hw_addr = top->bus_mem_addr;
			old_hw_addr = top->bus_mem_addr;
			

			pix_count++;

			// Write VGA output to a file. RAW RGB!
			rgb[0] = top->VGA_R << 4;	// GBA core outputs 4 bits per VGA colour channel (12 bpp).
			rgb[1] = top->VGA_G << 4;
			rgb[2] = top->VGA_B << 4;
			//fwrite(rgb, 1, 3, vgap);		// Write 24-bit values to the file.
			uint32_t vga_addr = (line_count * 1024) + pix_count;
			if (vga_addr <= vga_size) vga_ptr[vga_addr] = (rgb[0] << 16) | (rgb[1] << 8) | (rgb[2] << 0);
			
			disp_ptr[vga_addr] = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8;	// Our debugger framebuffer is in the 32-bit RGBA format.

				 // (line_count * width) + pixel_count.
			//uint32_t disp_addr = (top->gba_top__DOT__gfx__DOT__gfx__DOT__vcount * 240) + top->gba_top__DOT__gfx__DOT__gfx__DOT__hcount;
			//disp_ptr[disp_addr] = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8;	// Our debugger framebuffer is in the 32-bit RGBA format.


			//printf("dis_w: %d  dis_h: %d  dis_x: %d  dis_y: %d\n", top->dis_w, top->dis_h, top->dis_x, top->dis_y);

			/*
			if (top->system_top__DOT__gp__DOT__vram_we) {
				rgb[0] = (top->system_top__DOT__gp__DOT__vram_bus_out & 0x001F) << 3;	// [4:0] Red.
				rgb[1] = (top->system_top__DOT__gp__DOT__vram_bus_out & 0x03E0) >> 2;	// [9:5] Green.
				rgb[2] = (top->system_top__DOT__gp__DOT__vram_bus_out & 0x7C00) >> 7;	// [14:10] Blue. Remember, the PS1 15 bpp format is in BGR order, so the upper bits are for Blue!
				disp_ptr[top->system_top__DOT__gp__DOT__vram_addr] = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8;	// Our debugger framebuffer is in the 32-bit RGBA format.

				if ((frame_count & 1) == 0) {
					vram_ptr[top->system_top__DOT__GPU_addr] = top->system_top__DOT__gp__DOT__vram_bus_out;
				}
				//else vram_ptr[top->system_top__DOT__GPU_addr] = 0xFFFF0000;	// Force a colour, because it's broken atm, and I can't see anything. ElectronAsh.
			}
			*/

			/*
			if (prev_sram_we_n == 0 && top->SRAM_WE_N == 1) {
				vram_ptr[top->SRAM_ADDR] = top->system_top__DOT__sram_dq_out;
				//printf("SRAM_WE_N: %d  SRAM_ADDR: %06x  SRAM_DQ: %04x\n", top->SRAM_WE_N, top->SRAM_ADDR, top->SRAM_DQ);
			}
			prev_sram_we_n = top->SRAM_WE_N;
			*/
			
			/*
			if (top->SRAM_OE_N == 0) {
				//rgb[0] = (vram_ptr[top->SRAM_ADDR] & 0xFF000000) >> 24;
				//rgb[1] = (vram_ptr[top->SRAM_ADDR] & 0x00FF0000) >> 16;
				//rgb[2] = (vram_ptr[top->SRAM_ADDR] & 0x0000FF00) >> 8;
				//top->SRAM_DQ = (rgb[0]<<7) | (rgb[1] << 2) | (rgb[0] >> 3);

				top->SRAM_DQ = vram_ptr[top->SRAM_ADDR];

				//printf("SRAM_OE_N: %d  SRAM_ADDR: %06x  SRAM_DQ: %04x\n", top->SRAM_OE_N, top->SRAM_ADDR, vram_ptr[top->SRAM_ADDR]);
			}
			*/

			if (prev_hsync && !top->VGA_HS) {
				//printf("Line Count: %d\n", line_count);
				//printf("Pix count: %d\n", pix_count);
				line_count++;
				pix_count = 0;
			}
			prev_hsync = top->VGA_HS;
			
			if (prev_vsync && !top->VGA_VS) {
				frame_count++;
				line_count = 0;
				printf("Frame: %06d  VSync! ", frame_count);
				
				//if (frame_count > 46) {
					printf("Dumping framebuffer to vga_out.raw!\n");
					char vga_filename[40];
					sprintf(vga_filename, "vga_frame_%d.raw", frame_count);
					vgap = fopen(vga_filename, "w");
					if (vgap != NULL) {
						printf("\nOpened %s for writing OK.\n", vga_filename);
					}
					else {
						printf("\nCould not open %s for writing!\n\n", vga_filename);
						return 0;
					};
					fseek(vgap, 0L, SEEK_SET);
				//}
				
				for (int i = 0; i < (1600 * 521); i++) {	// Pixels per line * total lines.
					//rgb[0] = vram_ptr[i] & 0x7C00 >> 7;
					//rgb[1] = vram_ptr[i] & 0x03E0 >> 2;
					//rgb[2] = vram_ptr[i] & 0x001F << 3;

					rgb[0] = (vga_ptr[i] & 0xFF000000) >> 24;
					rgb[1] = (vga_ptr[i] & 0x00FF0000) >> 16;
					rgb[2] = (vga_ptr[i] & 0x0000FF00) >> 8;

					//if (frame_count > =75) fwrite(rgb, 1, 3, vgap);	// Write pixels to the file.
					fwrite(rgb, 3, 1, vgap);	// Write pixels to the file.
				}
				//if (frame_count > 46) fclose(vgap);
				fclose(vgap);

				//printf("pc: %08X  addr: %08X  inst: %08X\n", top->pc << 2, top->bus_mem_addr, top->inst);
			}
			prev_vsync = top->VGA_VS;

			//if (top->VGA_we==1) printf("VGA_we is High!\n");

			//if (top->SRAM_DQ > 0) printf("SRAM_DQ is High!!!\n");
			//if (top->VGA_R > 0 || top->VGA_G > 0 || top->VGA_B > 0) printf("VGA is High!!!\n");
		}

		top->eval();            // Evaluate model!

		main_time++;            // Time passes...

		return 1;
	}
	// Stop Verilating...
	top->final();
	delete top;
	exit(0);
	return 0;
}


int my_count = 0;

static MemoryEditor mem_edit_1;

int main(int argc, char** argv, char** env) {

	// Create application window
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
	RegisterClassEx(&wc);
	HWND hwnd = CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX11 Example"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (CreateDeviceD3D(hwnd) < 0)
	{
		CleanupDeviceD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	// Show the window
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);


	Verilated::commandArgs(argc, argv);
	
	memset(vram_ptr, 0x00, vram_size);
	memset(disp_ptr, 0xAA, disp_size);
	memset(vga_ptr,  0xAA, vga_size);

	memset(ram_ptr, 0x00, ram_size);
	
	/*
	// Can't get this to work without it segfaulting atm? OzOnE.
	FILE *fontp;
	fontp = fopen("fontRomData.bin","r");
	if (fontp!=NULL) {
		printf("\nLoaded Font ROM file OK.\n\n");
	} else {
		printf("\nFont ROM file not found!\n\n");
		return 0;
	};	
	for (uint32_t i=0;i<2048;i++) {
		fread(buffer, 1, 1, fontp);
		uint32_t font_data = buffer[0];
		osd->set_mem(i, font_data);
	};
	*/
	
	unsigned int file_size;

	FILE *biosfile;
	const char* bios_filename = "gbabios.bin";
	biosfile = fopen(bios_filename,"r");
	
	if (biosfile!=NULL) printf("\GBA BIOS %s loaded OK.\n\n", bios_filename);
	else { printf("\GBA BIOS file not found!\n\n"); return 0; }
		
	fseek(biosfile, 0L, SEEK_END);
	file_size = ftell(biosfile);
	fseek(biosfile, 0L, SEEK_SET);
	fread(bios_ptr, 1, bios_size, biosfile);	// Read the whole ROM file into RAM.


	FILE *cartfile;
	const char* cart_filename = "pong.gba";
	cartfile = fopen(cart_filename, "r");

	if (cartfile != NULL) printf("\GBA CART %s loaded OK.\n\n", cart_filename);
	else { printf("\GBA CART file not found!\n\n"); return 0; }

	fseek(cartfile, 0L, SEEK_END);
	file_size = ftell(biosfile);
	fseek(cartfile, 0L, SEEK_SET);
	fread(cart_ptr, 1, cart_size, cartfile);	// Read the whole ROM file into RAM.


	/*
	FILE *expfile;
	expfile = fopen("CAETLA38.BIN", "r");

	if (expfile != NULL) printf("\nPS1 Expansion ROM loaded OK.\n\n");
	else { printf("\nPS1 Expansion ROM file not found!\n\n"); return 0; }

	fseek(expfile, 0L, SEEK_END);
	file_size = ftell(expfile);
	fseek(expfile, 0L, SEEK_SET);
	fread(exp_ptr, 1, exp_size, expfile);	// Read the whole EXPANSION ROM file.
	*/

	/*
	FILE *ramfile;
	ramfile = fopen("ps1ram.bin","r");
	
	if (ramfile!=NULL) printf("\nRAM file opened OK.\n");
	else { printf("\nRAM file not found!\n\n"); return 0; }
	
	fseek(ramfile, 0L, SEEK_END);
	file_size = ftell(ramfile);
	fseek(ramfile, 0L, SEEK_SET);
	fread(ram_ptr, 1, 0x200000, ramfile);
	*/

	/*
	FILE *exefile;
	exefile = fopen("TREX.EXE","r");
	//exefile = fopen("psxtest_cpu.exe","r");
	//exefile = fopen("PSXPAINT.EXE","r");
	//exefile = fopen("20anniversary.psx","r");
	//exefile = fopen("PSXTEST.EXE","r");
	//exefile = fopen("INTRO.EXE","r");
	//exefile = fopen("HAUNTRO.EXE","r");
	//exefile = fopen("avecpsx","r");
	//exefile = fopen("ELITE.PSX","r");
	
	if (exefile!=NULL) printf("\nEXE file opened OK.\n");
	else { printf("\nEXE file not found!\n\n");return 0; }
	fseek(exefile, 0L, SEEK_END);
	file_size = ftell(exefile);
	fseek(exefile, 0L, SEEK_SET);
	fread(exe_ptr, 1, exe_size, exefile);	// Read the whole EXE file into RAM.
	*/

	
	/*
	vgap = fopen("vga_out.raw","w");
	if (vgap!=NULL) {
		printf("\nOpened vga_out.raw for writing OK.\n");
	}
	else {	
		printf("\nCould not open vga_out.raw for writing!\n\n");
		return 0;
	};
	*/

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	// Build texture atlas
	int width = 1024;
	int height = 512;

	// Upload texture to graphics system
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//desc.Format = DXGI_FORMAT_B5G5R5A1_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ID3D11Texture2D *pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = disp_ptr;
	//subResource.pSysMem = vga_ptr;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, &g_pFontTextureView);
	pTexture->Release();

	// Store our identifier
	ImTextureID my_tex_id = (ImTextureID)g_pFontTextureView;

	
	// Create texture sampler
	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.MipLODBias = 0.f;
		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		desc.MinLOD = 0.f;
		desc.MaxLOD = 0.f;
		g_pd3dDevice->CreateSamplerState(&desc, &g_pFontSampler);
	}


	bool follow_writes = 0;
	int write_address = 0;
	
	// imgui Main loop stuff...
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		// Poll and handle messages (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//if (show_demo_window)
		//	ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		static float f = 0.1f;
		static int counter = 0;

		ImGui::Begin("Virtual Dev Board v1.0");		// Create a window called "Virtual Dev Board v1.0" and append into it.

		//ImGui::Text("Verilator sim running... ROM_ADDR: 0x%05x", top->ROM_ADDR);               // Display some text (you can use a format strings too)
																							   //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
																							   //ImGui::Checkbox("Another Window", &show_another_window);

		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

																//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
																//counter++;

																//ImGui::SameLine();
																//ImGui::Text("counter = %d", counter);
		//ImGui::Text("samp_index = %d", samp_index);
		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, "sample", -1.0f, 1.0f, ImVec2(0, 80));
		if (ImGui::Button("RESET")) main_time = 0;
		ImGui::Text("main_time %d", main_time);
		ImGui::Text("frame_count: %d  line_count: %d", frame_count, line_count);
		ImGui::Text("Addr:   0x%08X", top->bus_mem_addr);
		//ImGui::Text("PC:     0x%08X", top->pc << 2);
		//ImGui::Text("Inst:   0x%08X", top->system_top__DOT__core__DOT__InstMem_In);

		//if (ImGui::Button("Reset!")) top->KEY = 0;
		//else top->KEY = 1;

		ImGui::Checkbox("RUN", &run_enable);

		if (single_step == 1) single_step = 0;
		if (ImGui::Button("Single Step")) {
			run_enable = 0;
			single_step = 1;
		}

		if (multi_step == 1) multi_step = 0;
		if (ImGui::Button("Multi Step")) {
			run_enable = 0;
			multi_step = 1;
		}
		ImGui::SameLine(); ImGui::SliderInt("Step amount", &multi_step_amount, 8, 1024);
		ImGui::Text("Last SDRAM WRITE. byte_addr: 0x%08X  write_data: 0x%08X  data_ben: 0x%01X\n", last_sdram_byteaddr, last_sdram_writedata, last_sdram_ben);	//  Note sd_data_i is OUT of the sim!

		ImGui::Image(my_tex_id, ImVec2(width, height), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
		ImGui::End();


		ImGui::Begin("RAM Editor - Offset is 0x02000000");
		ImGui::Checkbox("Follow Writes", &follow_writes);
		if (follow_writes) write_address = (top->bus_mem_addr & 0x00FFFFFF) >> 2;
		mem_edit_1.DrawContents(ram_ptr, ram_size, 0);
		ImGui::End();
		

		ImGui::Begin("CPU Registers");
		ImGui::Spacing();
		ImGui::Text("r0       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r0);
		ImGui::Text("r1       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r1);
		ImGui::Text("r2       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r2);
		ImGui::Text("r3       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r3);
		ImGui::Text("r4       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r4);
		ImGui::Text("r5       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r5);
		ImGui::Text("r6       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r6);
		ImGui::Text("r7       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r7);
		ImGui::Text("r8       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r8);
		ImGui::Text("r9       0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r9);
		ImGui::Text("r10      0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r10);
		ImGui::Text("r11      0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r11);
		ImGui::Text("r12      0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__r12);
		ImGui::Text("r13 (sp) 0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__sp);
		ImGui::Text("r14 (lr) 0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__regfile_Inst__DOT__lr);
		ImGui::Text("r15 (pc) 0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__RegFile_PCIn);
		ImGui::Spacing();
		//ImGui::Text("bus_addr: 0x%08X", top->gba_top__DOT__bus_addr);
		//ImGui::Text("bus_mem_addr: 0x%08X", top->gba_top__DOT__bus_mem_addr);
		ImGui::Text("ADDR:    0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__ADDR);
		ImGui::Text("RDATA:   0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__RDATA);
		ImGui::Text("WDATA:   0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__WDATA);
		ImGui::Text("SIZE:    0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__SIZE);
		ImGui::Spacing();
		ImGui::Text("InstLat: 0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__controllogic_Inst__DOT__InstForDecodeLatched);
		ImGui::Spacing();
		ImGui::Text("ALU_AND:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_AND_Op);
		ImGui::Text("ALU_ORR:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_ORR_Op);
		ImGui::Text("ALU_EOR:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_EOR_Op);
		ImGui::Text("ALU_Ain:   0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__ABM_ABusOut);
		ImGui::Text("ALU_Bin:   0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__Shifter_ShOut);
		ImGui::Text("ALU_Dout:  0x%08X", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_DataOut);
		ImGui::Text("ALU_InvA:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_InvA);
		ImGui::Text("ALU_InvB:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_InvB);
		ImGui::Text("ALU_PassA: %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_PassA);
		ImGui::Text("ALU_PassB: %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_PassB);
		ImGui::Spacing();
		ImGui::Text("C_flag:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_CFlagOut);
		ImGui::Text("V_flag:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_VFlagOut);
		ImGui::Text("N_flag:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_NFlagOut);
		ImGui::Text("Z_flag:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ALU_ZFlagOut);
		ImGui::Spacing();
		ImGui::Text("AdrToPC: %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__AMI_AdrToPCSel);
		ImGui::Text("AdrInc:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__AMI_AdrIncStep);
		ImGui::Text("AdrCnt:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__AMI_AdrCntEn);
		ImGui::Text("PCInc:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__AMI_PCIncStep);
		ImGui::Spacing();
		ImGui::Text("nRESET:  %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__nRESET);
		ImGui::Text("pause:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__PAUSE);
		ImGui::Text("nIRQ:    %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__nIRQ);
		ImGui::Text("nFIQ:    %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__nFIQ);
		ImGui::Text("write:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__WRITE);
		ImGui::Text("abort:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__ABORT);


		ImGui::Begin("Control Logic");
		ImGui::Spacing();
		ImGui::Text("IDC_B:    %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__controllogic_Inst__DOT__IDC_B);
		ImGui::Text("IDC_BL:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__controllogic_Inst__DOT__IDC_BL);
		ImGui::Text("IDC_BX:   %d", top->gba_top__DOT__cpu__DOT__cpu__DOT__controllogic_Inst__DOT__IDC_BX);
		ImGui::End();

		/*
		ImGui::Text("at:   0x%08X", top->gba_top__DOT);
		ImGui::Text("v0:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[2]);
		ImGui::Text("v1:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[3]);
		ImGui::Text("a0:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[4]);
		ImGui::Text("a1:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[5]);
		ImGui::Text("a2:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[6]);
		ImGui::Text("a3:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[7]);
		ImGui::Text("t0:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[8]);
		ImGui::Text("t1:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[9]);
		ImGui::Text("t2:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[10]);
		ImGui::Text("t3:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[11]);
		ImGui::Text("t4:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[12]);
		ImGui::Text("t5:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[13]);
		ImGui::Text("t6:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[14]);
		ImGui::Text("t7:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[15]);
		ImGui::Text("s0:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[16]);
		ImGui::Text("s1:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[17]);
		ImGui::Text("s2:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[18]);
		ImGui::Text("s3:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[19]);
		ImGui::Text("s4:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[20]);
		ImGui::Text("s5:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[21]);
		ImGui::Text("s6:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[22]);
		ImGui::Text("s7:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[23]);
		ImGui::Text("t8:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[24]);
		ImGui::Text("t9:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[25]);
		ImGui::Text("k0:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[26]);
		ImGui::Text("k1:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[27]);
		ImGui::Text("gp:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[28]);
		ImGui::Text("sp:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[29]);
		ImGui::Text("fp:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[30]);
		ImGui::Text("ra:   0x%08X", top->system_top__DOT__core__DOT__RegisterFile__DOT__registers[31]);
		*/
		ImGui::End();

		/*
		ImGui::Begin("HW Registers");
		if (ImGui::CollapsingHeader("EXP / DLY Regs"))	//, ImGuiTreeNodeFlags_DefaultOpen
		{
			ImGui::Text("0x1F801000: EXP1_BASE:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__MEM_CTRL_1[0]);
			ImGui::Text("0x1F801004: EXP2_BASE:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__MEM_CTRL_1[1]);
			ImGui::Text("0x1F801008: EXP1_DLY:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__MEM_CTRL_1[2]);
			ImGui::Text("0x1F80100C: EXP3_DLY:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__MEM_CTRL_1[3]);
			ImGui::Text("0x1F801010: BIOS_DLY:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__MEM_CTRL_1[4]);
			ImGui::Text("0x1F801014: SPU_DLY:     0x%08X", top->system_top__DOT__memory__DOT__io__DOT__MEM_CTRL_1[5]);
			ImGui::Text("0x1F801018: CDROM_DLY:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__MEM_CTRL_1[6]);
			ImGui::Text("0x1F80101C: EXP2_DLY:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__MEM_CTRL_1[7]);
			ImGui::Text("0x1F801020: COM_DLY:     0x%08X", top->system_top__DOT__memory__DOT__io__DOT__MEM_CTRL_1[8]);
		}	

		if (ImGui::CollapsingHeader("SIO Regs"))	//, ImGuiTreeNodeFlags_DefaultOpen
		{
			ImGui::Text("0x1F801050: SIO_DATA:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__PERIPHERAL_IO[4]);
			ImGui::Text("0x1F801054: SIO_STAT:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__PERIPHERAL_IO[5]);
			ImGui::Text("0x1F801058: SIO_MODE:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__PERIPHERAL_IO[6]);
			ImGui::Text("0x1F80105A: SIO_CTRL:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__PERIPHERAL_IO[7]);
			//ImGui::Text("0x1F80105C: SIO_MISC:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__SIO_MISC);
			//ImGui::Text("0x1F80105E: SIO_BAUD:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__SIO_BAUD);
		}

		if (ImGui::CollapsingHeader("Int / MEMCON regs"))	//, ImGuiTreeNodeFlags_DefaultOpen
		{
			ImGui::Text("0x1F801060: RAM_SIZE:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__MEM_CTRL_2);
			ImGui::Text("0x1F801070: I_STAT:      0x%08X", top->system_top__DOT__memory__DOT__io__DOT__I_STAT);
			ImGui::Text("0x1F801074: I_MASK:      0x%08X", top->system_top__DOT__memory__DOT__io__DOT__I_MASK);
		}

		if (ImGui::CollapsingHeader("DMA Regs"))	//, ImGuiTreeNodeFlags_DefaultOpen
		{
			ImGui::Text("0x1F801080: DMA0_MADR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA0_MADR);
			ImGui::Text("0x1F801090: DMA1_MADR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA1_MADR);
			ImGui::Text("0x1F8010A0: DMA2_MADR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA2_MADR);
			ImGui::Text("0x1F8010B0: DMA3_MADR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA3_MADR);
			ImGui::Text("0x1F8010C0: DMA4_MADR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA4_MADR);
			ImGui::Text("0x1F8010D0: DMA5_MADR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA5_MADR);
			ImGui::Text("0x1F8010E0: DMA6_MADR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA6_MADR);
			ImGui::Text("0x1F801084: DMA0_BCR:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA0_BCR);
			ImGui::Text("0x1F801094: DMA1_BCR:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA1_BCR);
			ImGui::Text("0x1F8010A4: DMA2_BCR:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA2_BCR);
			ImGui::Text("0x1F8010B4: DMA3_BCR:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA3_BCR);
			ImGui::Text("0x1F8010C4: DMA4_BCR:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA4_BCR);
			ImGui::Text("0x1F8010D4: DMA5_BCR:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA5_BCR);
			ImGui::Text("0x1F8010E4: DMA6_BCR:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA6_BCR);
			ImGui::Text("0x1F801088: DMA0_CHCR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA0_CHCR);
			ImGui::Text("0x1F801098: DMA1_CHCR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA1_CHCR);
			ImGui::Text("0x1F8010A8: DMA2_CHCR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA2_CHCR);
			ImGui::Text("0x1F8010B8: DMA3_CHCR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA3_CHCR);
			ImGui::Text("0x1F8010C8: DMA4_CHCR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA4_CHCR);
			ImGui::Text("0x1F8010D8: DMA5_CHCR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA5_CHCR);
			ImGui::Text("0x1F8010E8: DMA6_CHCR:   0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA6_CHCR);
			ImGui::Text("0x1F8010F0: DMA_DPCR:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA_DPCR);
			ImGui::Text("0x1F8010F4: DMA_DICR:    0x%08X", top->system_top__DOT__memory__DOT__io__DOT__DMA_DICR);
			ImGui::Text("DMA2 curr_mode2_pntr:    0x%08X", top->system_top__DOT__memory__DOT__dma_c__DOT__dma2__DOT__curr_mode2_pntr);
			ImGui::Text(" DMA2 curr_mode2_cnt:    0x%08X", top->system_top__DOT__memory__DOT__dma_c__DOT__dma2__DOT__curr_mode2_cnt);
		}

		if (ImGui::CollapsingHeader("DMA Debugging"))	//, ImGuiTreeNodeFlags_DefaultOpen
		{
			ImGui::Text("DMA addr_interp  curr_state: %d", top->system_top__DOT__memory__DOT__addr_interp__DOT__curr_state);
			ImGui::Text("DMA Controller   curr_state: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__curr_state);
			ImGui::Text("DMA Channel0     curr_state: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma0__DOT__curr_state);
			ImGui::Text("DMA Channel1     curr_state: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma1__DOT__curr_state);
			ImGui::Text("DMA Channel2     curr_state: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma2__DOT__curr_state);
			ImGui::Text("DMA Channel3     curr_state: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma3__DOT__curr_state);
			ImGui::Text("DMA Channel4     curr_state: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma4__DOT__curr_state);
			ImGui::Text("DMA Channel5     curr_state: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma5__DOT__curr_state);
			ImGui::Text("DMA Channel6     curr_state: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma6__DOT__curr_state);
			ImGui::Text("DMA Channel6            tip: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma6__DOT__tip);
			ImGui::Text("DMA Channel6      sync_mode: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma6__DOT__sync_mode);
			ImGui::Text("DMA Channel6       first_tx: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma6__DOT__first_tx);
			ImGui::Text("DMA Channel6  mem_direction: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma6__DOT__mem_direction);
			ImGui::Text("DMA Channel6 curr_mode0_cnt: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma6__DOT__curr_mode0_cnt);
			ImGui::Text("DMA Channel0      fifo_full: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma0__DOT__chan_fifo_full);
			ImGui::Text("DMA Channel1      fifo_full: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma1__DOT__chan_fifo_full);
			ImGui::Text("DMA Channel2      fifo_full: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma2__DOT__chan_fifo_full);
			ImGui::Text("DMA Channel3      fifo_full: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma3__DOT__chan_fifo_full);
			ImGui::Text("DMA Channel4      fifo_full: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma4__DOT__chan_fifo_full);
			ImGui::Text("DMA Channel5      fifo_full: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma5__DOT__chan_fifo_full);
			ImGui::Text("DMA Channel6      fifo_full: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma6__DOT__chan_fifo_full);
			ImGui::Text("DMA dma_addr: %08X", top->system_top__DOT__memory__DOT__dma_c__DOT__dma_addr);
			ImGui::Text("DMA dma_ren: %d", top->system_top__DOT__dma_ren);
			ImGui::Text("DMA dma_wen: %d", top->system_top__DOT__dma_wen);
			ImGui::Text("DMA dma_ack: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma_ack);
			ImGui::Text("DMA dma_req: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma_req);
			ImGui::Text("DMA dma_done: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma_done);
			ImGui::Text("DMA dma0_start: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma0_start);
			ImGui::Text("DMA dma1_start: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma1_start);
			ImGui::Text("DMA dma2_start: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma2_start);
			ImGui::Text("DMA dma3_start: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma3_start);
			ImGui::Text("DMA dma4_start: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma4_start);
			ImGui::Text("DMA dma5_start: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma5_start);
			ImGui::Text("DMA dma6_start: %d", top->system_top__DOT__memory__DOT__dma_c__DOT__dma6_start);
			ImGui::Text("DMA dma0_i: %05X", top->system_top__DOT__memory__DOT__dma_c__DOT__dma0_i);
			ImGui::Text("DMA dma1_i: %05X", top->system_top__DOT__memory__DOT__dma_c__DOT__dma1_i);
			ImGui::Text("DMA dma2_i: %05X", top->system_top__DOT__memory__DOT__dma_c__DOT__dma2_i);
			ImGui::Text("DMA dma3_i: %05X", top->system_top__DOT__memory__DOT__dma_c__DOT__dma3_i);
			ImGui::Text("DMA dma4_i: %05X", top->system_top__DOT__memory__DOT__dma_c__DOT__dma4_i);
			ImGui::Text("DMA dma5_i: %05X", top->system_top__DOT__memory__DOT__dma_c__DOT__dma5_i);
			ImGui::Text("DMA dma6_i: %05X", top->system_top__DOT__memory__DOT__dma_c__DOT__dma6_i);
			ImGui::Text("DMA t_priority: %02X", top->system_top__DOT__memory__DOT__dma_c__DOT__t_priority);
			ImGui::Text("DMA MADR_new: %02X", top->system_top__DOT__memory__DOT__dma_c__DOT__DMA_MADR_new);
			ImGui::Text("DMA MADR_incr: %02X", top->system_top__DOT__memory__DOT__dma_c__DOT__DMA_MADR_incr);
			ImGui::Text("DMA MADR_decr: %02X", top->system_top__DOT__memory__DOT__dma_c__DOT__DMA_MADR_decr);
		}


		if (ImGui::CollapsingHeader("GPU Regs", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (top->system_top__DOT__gp__DOT__decode_state == 0 && top->system_top__DOT__gp__DOT__cmd_fifo_empty == 0) first_cmd_word = top->system_top__DOT__gp__DOT__cmd_fifo_cmd;
			ImGui::Text("GPU                  to_gp0: %d", top->system_top__DOT__gp__DOT__to_gp0);
			ImGui::Text("GPU                  to_gp1: %d", top->system_top__DOT__gp__DOT__to_gp1);
			ImGui::Text("GPU                gpu_stat: %08X", top->gpu_stat);
			ImGui::Text("GPU                gpu_read: %08X", top->gpu_read);
			ImGui::Text("GPU            gpu_main_bus: %08X", top->gpu_main_bus);
			ImGui::Text("GPU             cmd_fifo_re: %d", top->system_top__DOT__gp__DOT__cmd_fifo_re);
			ImGui::Text("GPU           cmd_fifo_full: %d", top->system_top__DOT__gp__DOT__cmd_fifo_full);
			ImGui::Text("GPU          cmd_fifo_empty: %d", top->system_top__DOT__gp__DOT__cmd_fifo_empty);
			ImGui::Text("GPU           cmd_fifo_dout: %08X", top->system_top__DOT__gp__DOT__cmd_fifo__DOT__data_out);
			ImGui::Text("GPU      cmd_fifo_queue_end: %d", top->system_top__DOT__gp__DOT__cmd_fifo__DOT__queue_end);
			ImGui::Text("GPU          first cmd word: %08X", first_cmd_word);
			ImGui::Text("GPU                cmd_hold: %02X", top->system_top__DOT__gp__DOT__cmd_hold);
			ImGui::Text("GPU            decode_state: %02X", top->system_top__DOT__gp__DOT__decode_state);
			ImGui::Text("GPU                wb_state: %02X", top->system_top__DOT__gp__DOT__wb_state);
			ImGui::Text("GPU          pipeline_stall: %d", top->system_top__DOT__gp__DOT__pipeline_stall);
			ImGui::Text("GPU                  cmd.x0: %d", top->system_top__DOT__gp__DOT__cmd_x0_debug);
			ImGui::Text("GPU                  cmd.x1: %d", top->system_top__DOT__gp__DOT__cmd_x1_debug);
			ImGui::Text("GPU                  cmd.y0: %d", top->system_top__DOT__gp__DOT__cmd_y0_debug);
			ImGui::Text("GPU                  cmd.y1: %d", top->system_top__DOT__gp__DOT__cmd_y1_debug);

			if (top->system_top__DOT__gp__DOT__c2v_state > 0) {
				ImGui::Text("GPU               c2v_state: %d", top->system_top__DOT__gp__DOT__c2v_state);
				ImGui::Text("GPU           c2v_vram_addr: %05X", top->system_top__DOT__gp__DOT__c2v_vram_addr);
				ImGui::Text("GPU                   c2v_x: %d", top->system_top__DOT__gp__DOT__c2v_x);
				ImGui::Text("GPU                   c2v_y: %d", top->system_top__DOT__gp__DOT__c2v_y);
				ImGui::Text("GPU                c2v_hold: %04X", top->system_top__DOT__gp__DOT__c2v_hold);
				ImGui::Text("GPU            c2v_low_read: %d", top->system_top__DOT__gp__DOT__c2v_low_read);
				ImGui::Text("GPU                  c2v_on: %d", top->system_top__DOT__gp__DOT__c2v_on);
				ImGui::Text("GPU             c2v_fifo_re: %d", top->system_top__DOT__gp__DOT__c2v_fifo_re);
				ImGui::Text("GPU                 c2v_rdy: %d", top->system_top__DOT__gp__DOT__c2v_rdy);
				ImGui::Text("GPU             c2v_vram_re: %d", top->system_top__DOT__gp__DOT__c2v_vram_re);
				ImGui::Text("GPU             c2v_vram_we: %d", top->system_top__DOT__gp__DOT__c2v_vram_we);
				ImGui::Text("GPU           c2v_vram_data: %04X", top->system_top__DOT__gp__DOT__c2v_vram_data);
				ImGui::Text("GPU          c2v_word_count: %d", top->system_top__DOT__gp__DOT__c2v_word_count);
			}

			if (top->system_top__DOT__gp__DOT__v2c_state > 0) {
				ImGui::Text("GPU               v2c_state: %d", top->system_top__DOT__gp__DOT__v2c_state);
				ImGui::Text("GPU                   v2c_x: %d", top->system_top__DOT__gp__DOT__v2c_x);
				ImGui::Text("GPU                   v2c_y: %d", top->system_top__DOT__gp__DOT__v2c_y);
				ImGui::Text("GPU                v2c_hold: %04X", top->system_top__DOT__gp__DOT__v2c_hold);
				ImGui::Text("GPU                  v2c_on: %d", top->system_top__DOT__gp__DOT__v2c_on);
				ImGui::Text("GPU                 v2c_rdy: %d", top->system_top__DOT__gp__DOT__v2c_rdy);
				ImGui::Text("GPU             v2c_vram_re: %d", top->system_top__DOT__gp__DOT__v2c_vram_re);
				ImGui::Text("GPU             vram_bus_in: 0x%02X", top->system_top__DOT__gp__DOT__vram_bus_in);
				ImGui::Text("GPU          v2c_word_count: %d", top->system_top__DOT__gp__DOT__v2c_word_count);
			}

			ImGui::Text("GPU        dma2_total_words: %d", top->system_top__DOT__memory__DOT__io__DOT__dma2_totalwords);
			//ImGui::Text("GPU               v2v_state: %d", top->system_top__DOT__gp__DOT__v2v_state);
			ImGui::Text("GPU              fill_state: %d", top->system_top__DOT__gp__DOT__fill_state);
			ImGui::Text("GPU            xy_gen_state: %d", top->system_top__DOT__gp__DOT__xy_gen_state);
			ImGui::Text("GPU                  GPU_en: %d", top->system_top__DOT__GPU_en);
			ImGui::Text("GPU                  GPU_we: %d", top->system_top__DOT__GPU_we);
			ImGui::Text("GPU             GPU_data_in: %04X", top->system_top__DOT__GPU_data_in);
			ImGui::Text("GPU                GPU_addr: %05X", top->system_top__DOT__GPU_addr);
			ImGui::Text("GPU               SRAM_ADDR: %05X", top->SRAM_ADDR);
			ImGui::Text("GPU                   my_r0: %02X", top->system_top__DOT__gp__DOT__my_r0);
			ImGui::Text("GPU                   my_g0: %02X", top->system_top__DOT__gp__DOT__my_g0);
			ImGui::Text("GPU                   my_b0: %02X", top->system_top__DOT__gp__DOT__my_b0);
			ImGui::Text("GPU                   my_r1: %02X", top->system_top__DOT__gp__DOT__my_r1);
			ImGui::Text("GPU                   my_g1: %02X", top->system_top__DOT__gp__DOT__my_g1);
			ImGui::Text("GPU                   my_b1: %02X", top->system_top__DOT__gp__DOT__my_b1);
			ImGui::Text("GPU                   my_r2: %02X", top->system_top__DOT__gp__DOT__my_r2);
			ImGui::Text("GPU                   my_g2: %02X", top->system_top__DOT__gp__DOT__my_g2);
			ImGui::Text("GPU                   my_b2: %02X", top->system_top__DOT__gp__DOT__my_b2);
			ImGui::Text("GPU                   undoc: %d", top->system_top__DOT__gp__DOT__undoc);
		}
		

		//if (top->system_top__DOT__gp__DOT__undoc) run_enable = 0;
		if (top->system_top__DOT__gp__DOT__c2v_state > 0) run_enable = 0;		// Stop on "CPU to VRAM" GPU commands.
		if (top->system_top__DOT__gp__DOT__v2c_state > 0) run_enable = 0;		// Stop on "VRAM to CPU" GPU commands.

		if (ImGui::CollapsingHeader("SPU Regs", ImGuiTreeNodeFlags_DefaultOpen))
		{
			//ImGui::Text("0x1F801D80: SPU_VOL:     0x%08X", top->sp
			//ImGui::Text("0x1F801D84: SPU_REVVOL:  0x%08X", top->
			//ImGui::Text("0x1F801DA8: SPU_FIFO:    0x%08X", top->
			//ImGui::Text("0x1F801DAC: SPU_TRNCON:  0x%08X", top->
		}

		//ImGui::Text("0x1F802000: ATCONSTAT:   0x%08X", top->
		//ImGui::Text("0x1F802002: ATCONDATA:   0x%08X", top->
				
		ImGui::Spacing();
		ImGui::Text("0xFFFE0130: BIU:         0x%08X", top->system_top__DOT__memory__DOT__io__DOT__CACHE_CTRL);

		ImGui::Spacing();
		ImGui::Text("0x1F802040: DIPSW/7SEG:  0x%08X", top->system_top__DOT__memory__DOT__addr_interp__DOT__DIPSW_7SEG);
		ImGui::End();
		*/

		//void ui_m6502_draw(ui_m6502_t* win);

		// 3. Show another simple window.
		/*
		if (show_another_window)
		{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
		show_another_window = false;
		ImGui::End();
		}
		*/

		// Update the texture!
		// D3D11_USAGE_DEFAULT MUST be set in the texture description (somewhere above) for this to work.
		// (D3D11_USAGE_DYNAMIC is for use with map / unmap.) ElectronAsh.
		g_pd3dDeviceContext->UpdateSubresource(pTexture, 0, NULL, disp_ptr, width * 4, 0);

		// Rendering
		ImGui::Render();
		g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
		g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		//g_pSwapChain->Present(1, 0); // Present with vsync
		g_pSwapChain->Present(0, 0); // Present without vsync

		if (run_enable) for (int step = 0; step < 1024; step++) verilate();	// Simulates MUCH faster if it's done in batches.
		else {																// But, that will affect the values we can grab for the GUI.
			if (single_step) verilate();
			if (multi_step) for (int step = 0; step < multi_step_amount; step++) verilate();
		}
	}
	// Close imgui stuff properly...
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	DestroyWindow(hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);

	return 0;
}