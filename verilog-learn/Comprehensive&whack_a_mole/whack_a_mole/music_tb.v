`timescale 1ns / 1ps

module music_tb();

reg rst;
reg clk;
reg silent;
reg [2:0] music_code;
wire buzzer;

localparam IDLE_MUSIC = 3'b000; // 空闲态，不发声
localparam START_MUSIC = 3'b001; // 开始游戏声音
localparam SUCCESSED_MUSIC = 3'b010; // 成功声音
localparam FAILED_MUSIC = 3'b011; // 失败声音
localparam NO_MUSIC = 3'b100; // 没有声音
localparam FINISHED_MUSIC = 3'b101; // 结束音乐

initial begin
    clk = 1'b0;
    rst = 1'b1;
    music_code = 3'b0;
    silent = 1'b0;
    #10;

    // 复位
    rst = 1'b0;
    #20;
    music_code = START_MUSIC;
    #1000000000;
    music_code = FAILED_MUSIC;
    #1000000000;
    music_code = SUCCESSED_MUSIC;
    #1000000000;
    music_code = FINISHED_MUSIC;
    #1000000000;
    music_code = NO_MUSIC;
    #300 $finish;
end
always #5 clk = ~clk;   //生成时钟

music U_music(
    .clk(clk),
    .rst(rst),
    .music_code(music_code),
    .silent(silent),
    .buzzer(buzzer)
);

endmodule