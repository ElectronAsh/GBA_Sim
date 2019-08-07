module square2 (
    input logic system_clock,
    input logic clock_256,
    input logic reset,
    input logic [7:0] NR21,
    input logic [7:0] NR22,
    input logic [7:0] NR23,
    input logic [7:0] NR24,
    output logic [23:0] output_wave);

    logic clock_128;
    logic clock_64;
    logic [23:0] square_wave;
    logic [23:0] length_wave;
    logic [3:0] volume_level;

    assign output_wave = (length_wave[23])  ? (length_wave - (volume_level << 16)) : (volume_level + (4'd1 << 16));
    clock_divider cd1(clock_256, reset, clock_128, clock_64);
    square_wave sw1(system_clock, reset, NR21, NR23, NR24, square_wave);
    length_counter lc1(clock_256, reset, square_wave, NR21, NR24, length_wave);
    volume_envelope ve1(clock_64, reset, NR22, volume_level);

endmodule: square2
