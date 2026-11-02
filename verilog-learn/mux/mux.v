module mux (
    input  wire       en,          // 1位使能
    input  wire       mux_sel,     // 1位选择信号
    input  wire [3:0] input_a,     // 4位输入数据a
    input  wire [3:0] input_b,     // 4位输入数据b
    output reg  [3:0] output_c     // 4位输出数据，驱动LED显示
);

always @ (*) begin
    if (en==1'b1) begin
        if (mux_sel == 1'b1)
            output_c = input_a - input_b;
        else
            output_c = input_a + input_b;
    end
    else output_c = 4'hf;
end

endmodule