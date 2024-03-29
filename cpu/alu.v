//--------------------------------------------------------------------------------------------
//
// Generated by X-HDL VHDL Translator - Version 2.0.0 Feb. 1, 2011
// Tue Jul 30 2019 21:09:53
//
//      Input file      : 
//      Component name  : alu
//      Author          : 
//      Company         : 
//
//      Description     : 
//
//
//--------------------------------------------------------------------------------------------

//****************************************************************************************************
// ALU for ARM core
// Designed by Ruslan Lepetenok
// Modified 16.12.2002
//****************************************************************************************************

module alu(
   ADataIn,
   BDataIn,
   DataOut,
   InvA,
   InvB,
   PassA,
   PassB,
   AND_Op,
   ORR_Op,
   EOR_Op,
   CFlagIn,
   CFlagUse,
   ThADR,
   CFlagOut,
   VFlagOut,
   NFlagOut,
   ZFlagOut
);
   input [31:0]  ADataIn;
   input [31:0]  BDataIn;
   output [31:0] DataOut;
   input         InvA;
   input         InvB;
   input         PassA;
   input         PassB;		// MOV/MVN operations
   // Logic operations
   input         AND_Op;
   input         ORR_Op;
   input         EOR_Op;
   // Flag inputs
   input         CFlagIn;
   input         CFlagUse;		// ADC/SBC/RSC instructions
   input         ThADR;		// THUMB ADD(5) correction
   // Flag outputs
   output        CFlagOut;
   output        VFlagOut;
   output        NFlagOut;
   output        ZFlagOut;
   
   
   wire [31:0]   AThFix;
   wire [31:0]   AXOROut;
   wire [31:0]   BXOROut;
   
   wire [31:0]   Adder;
   wire [31:0]   Carry;
   
   wire [31:0]   LUOut;
   
   wire [31:0]   ALUResult;
   
   wire          nL_A;		// '0' -> Logic op./'1' -> Arith. op.
   
   // Instruction type detecter
   assign nL_A = (~(AND_Op | ORR_Op | EOR_Op));
   
   // A-Bus (R15) THUMB ADR correction
   assign AThFix = (ThADR == 1'b1) ? ADataIn & 32'hFFFFFFFC : 
                   ADataIn;
   
   // A-bus XOR gate (inverter)
   assign AXOROut = (InvA == 1'b1) ? (~AThFix) : 
                    AThFix;
   
   // B-bus XOR gate (inverter)
   assign BXOROut = (InvB == 1'b1) ? (~BDataIn) : 
                    BDataIn;
   
   // Adder
   assign Adder[0] = AXOROut[0] ^ BXOROut[0] ^ ((CFlagIn & CFlagUse) ^ (InvA | InvB));
   assign Carry[0] = (AXOROut[0] & BXOROut[0]) | ((AXOROut[0] | BXOROut[0]) & ((CFlagIn & CFlagUse) ^ (InvA | InvB)));
   generate
      begin : xhdl0
         genvar        i;
         for (i = 1; i <= 31; i = i + 1)
         begin : AdderLogic
            assign Adder[i] = AXOROut[i] ^ BXOROut[i] ^ Carry[i - 1];
            assign Carry[i] = (AXOROut[i] & BXOROut[i]) | ((AXOROut[i] | BXOROut[i]) & Carry[i - 1]);
         end
      end
   endgenerate
   
   // Logic unit output multiplexer
   generate
      begin : xhdl1
         genvar        i;
         for (i = 31; i >= 0; i = i - 1)
         begin : LogicUnitOutMUX
            // AND
            assign LUOut[i] = (AXOROut[i] & BXOROut[i] & AND_Op) | ((AXOROut[i] | BXOROut[i]) & ORR_Op) | ((AXOROut[i] ^ BXOROut[i]) & EOR_Op);		// ORR
         end
      end
   endgenerate
   // EOR
   
   assign ZFlagOut = (ALUResult == 32'h0000_0000);
   assign NFlagOut = ALUResult[31];
   assign CFlagOut = (nL_A == 1'b1 & PassB == 1'b0) ? Carry[31] : 
                     CFlagIn;
   
   assign VFlagOut = (AXOROut[31] & BXOROut[31] & (~Adder[31])) | ((~AXOROut[31]) & (~BXOROut[31]) & Adder[31]);
   // ADD/ADC/CMN,SUB/SBC/RSB/RSC/CMP
   
   generate
      begin : xhdl2
         genvar        i;
         for (i = 31; i >= 0; i = i - 1)
         begin : ALUResultMUX
            // MOV/MVN
            assign ALUResult[i] = (ADataIn[i] & PassA) | (BXOROut[i] & PassB) | (Adder[i] & nL_A & (~(PassA | PassB))) | (LUOut[i] & (~nL_A) & (~(PassA | PassB)));		// ADD/ADC,SUB/SBC,RSB/RSC,(CMP/CMN)
         end
      end
   endgenerate
   // AND/EOR/ORR,BIC,(TST/TEQ)
   
   assign DataOut = ALUResult;
   
endmodule
