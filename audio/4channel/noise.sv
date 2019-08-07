module noise (
    input logic system_clock,
    input logic clock_256,
    input logic reset,
    input logic [7:0] NR41,
    input logic [7:0] NR42,
    input logic [7:0] NR43,
    input logic [7:0] NR44,
    output logic [23:0] output_wave);

    logic clock_128;
    logic clock_64;
    logic [23:0] noise_wave;
    logic [23:0] length_wave;
    logic [3:0] volume_level;

    assign output_wave = (length_wave[23])  ? (length_wave - (volume_level << 16)) 
                            : (length_wave + (volume_level << 16));

    clock_divider cd3(clock_256, reset, clock_128, clock_64);
    noise_channel nc3(system_clock, reset, NR43, noise_wave);
    length_counter lc3(clock_256, reset, noise_wave, NR41, NR44, length_wave);
    volume_envelope ve3(clock_64, reset, NR42, volume_level);

endmodule: noise
