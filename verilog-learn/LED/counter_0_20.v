`timescale 1ns / 1ps

module counter_0_20#(
    parameter COUNT_TIME = 24'd10000000-1,    // 周期为0.1s，即0.10000000s
    parameter DEBOUNCE_TIME = 24'd2000000 - 1 //消抖时间，默认为20ms，即0.02000000s
)(
    input wire clk,
    input wire rst,
    input wire button,

    output reg [7:0] cnt
    );
    // // 测试
    // always @(*) begin
    //     if (button)begin
    //         count = 8'h88;
    //     end
    //     else begin
    //         count = 8'h66;
    //     end
    // end

    //边沿检测 上升沿和下降沿均可
    reg sig_r0;
    reg sig_r1;

    always @(posedge clk or posedge rst) begin
        if (rst)begin
            sig_r0 <= 1'b0;
            sig_r1 <= 1'b0;
        end
        else begin
            sig_r0 <= button;
            sig_r1 <= sig_r0;
        end
    end

    wire pos_edge = sig_r1 ^ sig_r0;

    // 实例化一个计数器，用于消抖
    wire [23:0] CNT_debounced;
    counter #(.CNT_MAX(DEBOUNCE_TIME)) u_counter_3  (
        .clk(clk),
        .rst(rst),
        .pause(1'b0),
        .one(1'b1),
        .reboot(pos_edge),
        .cnt(CNT_debounced)
        );

    reg pause;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            pause <= 1'd0;
        end
        else if (CNT_debounced == DEBOUNCE_TIME) begin
            pause <= button;
        end
    end


    // 实例化一个计数器,用于数数
    wire [23:0] CNT;
    counter #(.CNT_MAX(COUNT_TIME)) u_counter_4 (
        .clk(clk),
        .rst(rst),
        .pause(pause),
        .one(1'b0),
        .reboot(1'b0),
        .cnt(CNT)
    );

    reg [6:0] count;
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            count <= 2'd0;
        end
        else if (CNT == COUNT_TIME) begin
            if (count < 19)begin
                count <= count + 1;
            end
            else begin
                count <= 2'd0;
            end
        end
    end


    wire [3:0] count_ten = count / 7'd10;
    wire [3:0] count_one = count % 7'd10;
    always @(*) begin
        cnt = {count_ten, count_one};
    end

endmodule
