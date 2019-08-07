module square1 (
    input logic system_clock,
    input logic clock_256,
    (* mark_debug = "true" *) input logic reset,
    input logic [7:0] NR10,
    input logic [7:0] NR11,
    input logic [7:0] NR12,
    input logic [7:0] NR13,
    input logic [7:0] NR14,
    output logic [23:0]output_wave); 

    logic clock_128;
    logic clock_64;
    logic enable_square_wave;
    logic [23:0] square_wave;
    logic [23:0] length_wave;
    logic [3:0] volume_level;
    logic [7:0] internal_NR13;
    logic [7:0] internal_NR14;
    
    //assign internal_NR13 = NR13;
    //assign internal_NR14 = NR14;

    //assign output_wave = length_wave;//(enable_square_wave) ? $signed(length_wave) >>> (16-volume_level) : 0;
    assign output_wave = (length_wave[23]) ? (length_wave - (volume_level << 16)) : (length_wave + (volume_level << 16)); 
    //give volume an aribitrary weight, but keep it consistant

    clock_divider cd(clock_256, reset,  clock_128, clock_64);
    //frequency_sweep fs(clock_128, reset, NR10, NR13, NR14, internal_NR13, internal_NR14, enable_square_wave);
    square_wave sw(system_clock, reset, NR11, NR13, NR14, square_wave);
    length_counter lc(clock_256, reset, square_wave, NR11, NR14, length_wave);
    volume_envelope ve(clock_64, reset, NR12, volume_level);
 
endmodule: square1
