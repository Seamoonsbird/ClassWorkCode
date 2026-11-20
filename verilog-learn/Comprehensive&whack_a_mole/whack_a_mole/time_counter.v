`timescale 1ns / 1ps

module time_counter(
    input wire clk,
    input wire rst,
    input wire start,
    input wire reboot,
    output reg [7:0] count
    );
    // 先实例化一个计数器
    // 周期是1.00000000s
    localparam COUNT_TIME = 29'd100000000-1;
    wire [28:0] cnt;
    counter #(.CNT_MAX(COUNT_TIME)) u_counter_1(
        .clk(clk),
        .rst(rst),
        .pause(1'b0),
        .one(1'b0),
        .reboot(start||reboot),
        .auto_start(1'b0),
        .cnt(cnt)
    );

    // 计算倒计时
    reg [4:0] count_raw;
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            count_raw <= 5'd20;
        end
        else if (reboot) begin
            count_raw <= 5'd20;
        end
        else if (cnt == COUNT_TIME) begin
            if (count_raw >5'b0) begin
                count_raw <= count_raw - 5'b1;
            end
            else begin
                count_raw <= count_raw;
            end
        end
        else begin
            count_raw <= count_raw;
        end
    end

    wire [3:0] count_ten = count_raw / 5'd10;
    wire [3:0] count_one = count_raw % 5'd10;
    always @(*) begin
        count = {count_ten, count_one};
    end

endmodule
