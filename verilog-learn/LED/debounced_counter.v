`timescale 1ns / 1ps

module debounced_counter #(
    parameter DEBOUNCE_TIME = 24'd2000000 - 1 //消抖时间，默认为20ms，即0.02000000s
)
(
    input wire clk,
    input wire rst,
    input wire key_in,
    output reg [7:0] cnt
);
    // // 测试
    // always @(*) begin
    //     if (key_in)begin
    //         cnt = 8'h88;
    //     end
    //     else begin
    //         cnt = 8'h66;
    //     end
    // ende
    
    //边沿检测 上升沿和下降沿均可
    reg sig_r0;
    reg sig_r1;

    always @(posedge clk or posedge rst) begin
        if (rst)begin
            sig_r0 <= 1'b0;
            sig_r1 <= 1'b0;
        end
        else begin
            sig_r0 <= key_in;
            sig_r1 <= sig_r0;
        end
    end

    wire pos_edge = sig_r1 ^ sig_r0;

    //实例化一个计数器
    wire [23:0] CNT;
    counter #(.CNT_MAX(DEBOUNCE_TIME)) u_counter_2  (
        .clk(clk),
        .rst(rst),
        .pause(1'b0),
        .one(1'b1),
        .reboot(pos_edge),
        .cnt(CNT)
        );

    reg [6:0] count;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            count <= 2'd0;
        end

        else if (CNT == DEBOUNCE_TIME) begin
            if (key_in) begin
                if (count < 99)begin
                    count <= count + 1;
                end
                else begin
                    count <= 2'd0;
                end
            end
        end
    end

    wire [3:0] count_ten = count / 7'd10;
    wire [3:0] count_one = count % 7'd10;
    always @(*) begin
        cnt = {count_ten, count_one};
    end


endmodule
