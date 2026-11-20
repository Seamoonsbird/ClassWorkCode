`timescale 1ns / 1ps

module music(
    input  wire       clk,        
    input  wire       rst,        
    input  wire       silent,
    input  wire [2:0] music_code,

    output reg        buzzer
);

// 先实例化一个计数器，用于产生2000Hz等的音乐
// 0.00050000s*2=0.00100000s
localparam FREQ_2000 = 17'd100000-1;
wire [28:0] count_2000;
counter #(FREQ_2000) u_counter_4(
    .clk(clk),
    .rst(rst),
    .pause(1'b0),
    .one(1'b0),
    .reboot(1'b0),
    .auto_start(1'b1),
    .cnt(count_2000)
);


// 再实例化一个计数器，用于改变音乐的时间
//0.10000000s
localparam MUSIC_TIME = 29'd010000000-1;
wire [28:0] music_time;
counter #(MUSIC_TIME) u_counter_5(
    .clk(clk),
    .rst(rst),
    .pause(1'b0),
    .one(1'b0),
    .reboot(1'b0),
    .auto_start(1'b1),
    .cnt(music_time)
);


reg [1:0] music_freq;
localparam IDLE_MUSIC = 3'b000; // 空闲态，不发声
localparam START_MUSIC = 3'b001; // 开始游戏声音
localparam SUCCESSED_MUSIC = 3'b010; // 成功声音
localparam FAILED_MUSIC = 3'b011; // 失败声音
localparam NO_MUSIC = 3'b100; // 没有声音
localparam FINISHED_MUSIC = 3'b101; // 结束音乐

localparam NO = 2'b00; // 没声
localparam LOW = 2'b01; // 低频
localparam MID = 2'b10; // 中频
localparam HIGH = 2'b11; // 高频

always @(posedge clk or posedge rst) begin
    if (rst) begin
        music_freq <= NO;// 复位不发声
    end
    else begin
        if (silent) begin
            music_freq <= NO;
        end
        else begin
            case (music_code)
                IDLE_MUSIC : 
                    music_freq <= LOW;
                START_MUSIC :
                    if (music_time == MUSIC_TIME) begin
                        music_freq <= music_freq + 1;
                    end
                SUCCESSED_MUSIC :
                    if ((music_time == MUSIC_TIME) || (music_time == MUSIC_TIME/2)) begin
                        if (music_freq == NO) begin
                            music_freq <= HIGH;
                        end
                        else begin
                            music_freq <= NO;
                        end
                    end
                FAILED_MUSIC :
                    music_freq <= MID;
                NO_MUSIC :
                    music_freq <= NO;
                FINISHED_MUSIC :
                    if ((music_time == MUSIC_TIME) || (music_time == MUSIC_TIME/3)) begin
                        if (music_freq == NO) begin
                            music_freq <= LOW;
                        end
                        else begin
                            music_freq <= NO;
                        end
                    end

                default: music_freq <= NO;
            endcase
        end
    end
end


// 根据music_freq来控制buzzer
always @(posedge clk or posedge rst) begin
    if (rst) begin
        buzzer <= 1'b0;
    end
    else begin
    case (music_freq)
        NO :
            buzzer <= 1'b0;
        HIGH :
            if ((count_2000 == FREQ_2000)||(count_2000 == FREQ_2000/2)||(count_2000 == FREQ_2000/4)||(count_2000 == (FREQ_2000*3)/4)) begin
                buzzer <= ~buzzer;
            end
            else begin
                buzzer <= buzzer;
            end
        MID :
            if ((count_2000 == FREQ_2000)||(count_2000 == FREQ_2000/2)) begin
                buzzer <= ~buzzer;
            end
            else begin
                buzzer <= buzzer;
            end
        LOW :
            if (count_2000 == FREQ_2000) begin
                buzzer <= ~buzzer;
            end
            else begin
                buzzer <= buzzer;
            end
        default: buzzer <= 1'b0;
    endcase
    end
end

endmodule