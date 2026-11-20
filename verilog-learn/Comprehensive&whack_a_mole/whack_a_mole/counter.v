`timescale 1ns / 1ps

module counter#(
    parameter CNT_MAX = 27'd200000-1//0.00200000s
    )
(
    input wire clk,
    input wire rst,
    input wire pause, // 暂停or继续
    input wire one, // 是否是一轮
    input wire reboot, // 重启按键，启动时会清零
    input wire auto_start,

    output reg [28:0] cnt
    );

    reg cnt_inc; // 自增条件
    wire cnt_end = cnt_inc & (cnt >= CNT_MAX); // 结束条件


    //边沿检测 上升沿(pause)
    reg sig_r0;
    reg sig_r1;

    always @(posedge clk or posedge rst) begin
        if (rst)begin
            sig_r0 <= 1'b0;
            sig_r1 <= 1'b0;
        end
        else begin
            sig_r0 <= pause;
            sig_r1 <= sig_r0;
        end
    end

    wire pos_edge = ~sig_r1 & sig_r0;

    reg init_done;
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            init_done <= 1'b0;
        end
        else if (!init_done) begin
            init_done <= 1'b1;
        end
    end

    // 自增条件
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            cnt_inc <= 1'b0;
        end
        else if (!init_done) begin
            // 初始化
            cnt_inc <= auto_start;
        end
        else if (pos_edge) begin
            // 暂停or继续
            cnt_inc <= ~cnt_inc;
        end
        else if (reboot) begin
            cnt_inc <= 1'b1;
        end
        else if (cnt_end & one) begin
            // 一轮并且结束了
            cnt_inc <= 1'b0;
        end
    end

    always @ (posedge clk or posedge rst) begin
        if(rst)          cnt <= 29'd0;       // 复位后计数器清零
        else if(cnt_end) cnt <= 29'd0;       // 计数结束后计数器清零
        else if(reboot)   cnt <= 29'd0;       // 按下重启立马清零
        else if(cnt_inc) cnt <= cnt + 29'd1; // 累加条件满足时，计数器累加
        else             cnt <= cnt; 
    end
endmodule
