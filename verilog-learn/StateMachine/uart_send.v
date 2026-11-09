`timescale 1ns / 1ps

module uart_send(
    input        clk,        
    input        rst,        
    input        valid,       // 为1表明接下来的8位data有效，只维持一个时钟周期
    input [7:0]  data,        // 待发送的8位数据
    output reg   dout         // 发送信号
);

localparam IDLE  = 2'b00;   // 空闲态，发送高电平
localparam START = 2'b01;   // 起始态，发送起始位
localparam DATA  = 2'b10;   // 数据态，将8位数据位发送出去
localparam STOP  = 2'b11;   // 停止态，发送停止位

localparam BAUD_CNT_MAX = 14'd10416-1;
localparam BIT_CNT_MAX = 3'o7;

reg [1:0] current_state;
reg [1:0] next_state;

// 波特率计数器
// 该计数器直接使用了实验四的计数器模块，因此会有一些多余的输入，比如pause，one，reboot等
wire [24:0] baud_cnt;
counter #(.CNT_MAX(BAUD_CNT_MAX)) U_counter_1 (
    .clk(clk),
    .rst(rst),
    .pause(1'b0),
    .one(1'b0),
    .reboot(current_state != next_state),
    .cnt(baud_cnt)
    );

// 发送位数计数器
reg [2:0] bit_cnt;
wire baud_sig;
assign baud_sig = (baud_cnt == BAUD_CNT_MAX);
always @(posedge clk or posedge rst) begin
    if (rst) begin
        bit_cnt <= 3'b0;
    end
    else if ((current_state == DATA) && (bit_cnt < BIT_CNT_MAX) && baud_sig) begin
        bit_cnt <= bit_cnt + 1'b1;
    end
    else if ((bit_cnt >= BIT_CNT_MAX) && (current_state == DATA) && baud_sig) begin
        bit_cnt <= 3'b0;
    end
end

// 竟然仿真文件里面出现了只有一个时钟周期有效的data，必须使用一个变量将这个data存起来😅
reg [7:0] data_cache;
always @(posedge clk or posedge rst) begin
    if (rst) begin
        data_cache <= 8'b0;
    end
    else if (valid) begin
        data_cache <= data;
    end
end

// 第1个always块，描述次态迁移到现态
always @(posedge clk or posedge rst) begin
    if(rst)  current_state <= IDLE;
    else     current_state <= next_state;
end


// 第2个always块，描述状态转移条件判断
always @(*) begin
    case (current_state)
        IDLE : 
            if (valid) begin
                next_state = START;
            end
            else begin
                next_state = IDLE;
            end
        START :
            if (baud_sig) begin
                next_state = DATA;
            end
            else begin
                next_state = START;
            end
        DATA :
            if ((bit_cnt == BIT_CNT_MAX) && (baud_sig)) begin
                next_state = STOP;
            end
            else begin
                next_state = DATA;
            end
        STOP :
            if (baud_sig) begin
                next_state = IDLE;
            end
            else begin
                next_state = STOP;
            end
        default : next_state = IDLE; 
    endcase
end

// 第3个always块，描述输出逻辑，也可以用next_state作判断，对时序不敏感的电路两者都可以。
always @(posedge clk or posedge rst) begin
    if(rst) dout <= 1'b0;
    else begin
        case(current_state)
            IDLE  :     dout <= 1'b1;
            START :     dout <= 1'b0;
            DATA  :     dout <= data_cache[bit_cnt];
            STOP  :     dout <= 1'b1;
            default :   dout <=1'b1;
        endcase
    end
end

endmodule
