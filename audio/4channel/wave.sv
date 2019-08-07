module wave (
    input logic system_clock,
    input logic clock_256,
    input logic reset,
    input logic [7:0] NR30,
    input logic [7:0] NR31,
    input logic [7:0] NR32,
    input logic [7:0] NR33,
    input logic [7:0] NR34,
    input logic [15:0] addr_0x90,
    input logic [15:0] addr_0x92,
    input logic [15:0] addr_0x94,
    input logic [15:0] addr_0x96,
    input logic [15:0] addr_0x98,
    input logic [15:0] addr_0x9A,
    input logic [15:0] addr_0x9C,
    input logic [15:0] addr_0x9E,
    output logic [23:0] output_wave);

    logic clock_128;
    logic clock_64;
    logic [23:0] predefined_wave;
    logic [3:0] volume_level;

    clock_divider cd2(clock_256, reset, clock_128, clock_64);
    wave_channel vw2(system_clock, reset, NR32, NR33, NR34,
                addr_0x90, addr_0x92, addr_0x94,
                addr_0x96, addr_0x98, addr_0x9A, addr_0x9C, addr_0x9E, predefined_wave);
    length_counter lc2(clock_256, reset, predefined_wave, NR31, NR34, output_wave);

endmodule: wave
