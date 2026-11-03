`timescale 1ns / 1ps

module LED#(
    parameter CNT_MAX = 24'd200000 - 1,        //数码管位选信号频率，方便缩短仿真频率
    parameter DEBOUNCE_TIME = 24'd2000000 - 1, //消抖时间，默认为20ms，即0.02000000s 
    parameter COUNT_TIME = 24'd10000000-1      //计数器自增时间
)(
    input wire rst,
    input wire clk,
    input wire change_task,
    input wire counter_key,
    input wire counter_0_20_key,


    output wire [7:0]  led_en,   // 位选信号
    output wire [7:0]  led_cx    // 段选信号，EGO1段选信号需16位或2组8位
);

reg [31:0] data;

led_ctrl_unit #(.CNT_MAX(CNT_MAX)) u_led_ctrl_unit(
    .rst(rst),
    .clk(clk),
    .display(data),
    .led_en(led_en),
    .led_cx(led_cx)
);

wire [7:0] undebounced_counter_data;
wire [7:0] debounced_counter_data;
wire [7:0] counter_0_20_data;

undebounced_counter u_undebounced_counter(
    .clk(clk),
    .rst(rst),
    .key_in(counter_key),
    .cnt(undebounced_counter_data)
    );

debounced_counter #(DEBOUNCE_TIME) u_debounced_counter(
    .clk(clk),
    .rst(rst),
    .key_in(counter_key),
    .cnt(debounced_counter_data)
    );

counter_0_20 #(COUNT_TIME, DEBOUNCE_TIME) u_counter0_20(
    .clk(clk),
    .rst(rst),
    .button(counter_0_20_key),
    .cnt(counter_0_20_data)
    );


always @(*) begin
    if (change_task) begin
        data = 32'h25310417;
    end
    else begin
        data = {8'h17, undebounced_counter_data, debounced_counter_data, counter_0_20_data};
    end
end


endmodule
