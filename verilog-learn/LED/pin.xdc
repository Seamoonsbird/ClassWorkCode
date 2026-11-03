set_property -dict { PACKAGE_PIN Y18 IOSTANDARD LVCMOS33 } [get_ports clk];
set_property -dict { PACKAGE_PIN R1  IOSTANDARD LVCMOS33 } [get_ports rst];
set_property -dict { PACKAGE_PIN W4  IOSTANDARD LVCMOS33 } [get_ports change_task];
set_property -dict { PACKAGE_PIN P5  IOSTANDARD LVCMOS33 } [get_ports counter_key];
set_property -dict { PACKAGE_PIN P1  IOSTANDARD LVCMOS33 } [get_ports counter_0_20_key];



# 段选约束 led_cx[7:0] = LED_{CA, CB, ..., DP}
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN F15 } [get_ports led_cx[7]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN F13 } [get_ports led_cx[6]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN F14 } [get_ports led_cx[5]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN F16 } [get_ports led_cx[4]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN E17 } [get_ports led_cx[3]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN C14 } [get_ports led_cx[2]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN C15 } [get_ports led_cx[1]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN E13 } [get_ports led_cx[0]]
# 位选约束，A18连接的最左边的数码管，依次类推
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN A18 } [get_ports led_en[7]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN A20 } [get_ports led_en[6]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN B20 } [get_ports led_en[5]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN E18 } [get_ports led_en[4]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN F18 } [get_ports led_en[3]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN D19 } [get_ports led_en[2]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN E19 } [get_ports led_en[1]]
set_property -dict { IOSTANDARD LVCMOS33 PACKAGE_PIN C19 } [get_ports led_en[0]]