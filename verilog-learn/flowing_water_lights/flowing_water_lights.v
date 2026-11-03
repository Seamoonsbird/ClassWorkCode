/*
基于计数器，实现时间间隔可调、方向可调、模式可调的8位流水灯，详细要求如下：

clk：时钟信号，接Y18（Minisys）或P17（EGO1）引脚，板载100MHz时钟。
rst：异步复位，接按键开关S1。每次按下S1，流水灯复位，只亮LED0，松开后LED根据以下设置开始流动。
freq_ctrl：频率设置，间隔可在0.00200000s、0.10000000s切换，对应的频率分别是500Hz、10Hz，接拨码开关SW0。
dir_ctrl：方向设置，左移右移控制，接拨码开关SW1。
mode_sel：模式设置，连续1个灯、2个灯亮，接拨码开关SW7。
led：流水灯输出信号，自选LED灯连接。
拨码开关上下与频率、方向、模式的对应自行决定，频率、方向、模式切换不能按复位之后才生效！！！
*/
`timescale 1ns / 1ps
module flowing_water_lights #(
    parameter  CNT_BIG = 24'd10000000 - 1,
    parameter CNT_SMALL = 24'd200000 - 1
    )
(
    input  wire clk,  //接Y18
    input  wire rst,    //接按键开关S1
    input  wire freq_ctrl, //接拨码开关SW0, 0是500Hz, 1是10Hz
    input  wire dir_ctrl, //接拨码开关SW1, 0是左移, 1是右移
    input  wire mode_sel, //接拨码开关SW2, 0是1个灯亮, 1是两个灯亮
    output reg  [7:0] led    //接GLD0-GLD8
);



//频率设置
reg [23:0] cnt_max;
always @(*) begin
    if (freq_ctrl)begin
        cnt_max = CNT_BIG;
    end
    else begin
        cnt_max = CNT_SMALL;
    end
end

//计数器
reg [23:0] cnt;

wire cnt_inc = 1'b1;   // 自增条件，自行填写
wire cnt_end = cnt_inc & (cnt >= cnt_max);   // 结束条件，自行填写 一定要用>= 不可以用==

always @ (posedge clk or posedge rst) begin
    if(rst)          cnt <= 24'd0;       // 复位后计数器清零
    else if(cnt_end) cnt <= 24'd0;       // 计数结束后计数器清零
    else if(cnt_inc) cnt <= cnt + 24'd1; // 累加条件满足时，计数器累加
    else             cnt <= cnt; 
end


//流水灯实现
reg mode_prev;
always @(posedge clk or posedge rst) begin
    if (rst)begin
        led <= 8'h01;
        mode_prev <= 1'b0;
    end
    else begin
        if (mode_sel != mode_prev)begin
            led <= mode_sel ? 8'h03 : 8'h01;
            mode_prev <= mode_sel;
        end
        else if (cnt_end) begin
            if (mode_sel) begin
                //2个灯亮
                if (dir_ctrl) begin
                    //右移
                    led <= {led[1:0], led[7:2]};
                end
                else begin
                    //左移
                    led <= {led[5:0], led[7:6]};
                end
            end
            else begin
                //1个灯亮
                if (dir_ctrl) begin
                    //右移
                    led <= {led[0], led[7:1]};
                end
                else begin
                    //左移
                    led <= {led[6:0], led[7]};
                end
            end
        end
    end
end

endmodule
