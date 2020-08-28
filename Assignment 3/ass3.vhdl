----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/26/2020 03:17:12 PM
-- Design Name: 
-- Module Name: ass3 - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;


-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ass3 is
  Port (
    clk: in std_logic
     );
end ass3;

architecture Behavioral of ass3 is

type mem is array(0 to 4095) of std_logic_vector(31 downto 0);
signal mem1 : mem;
type reg is array(0 to 31) of std_logic_vector(31 downto 0);
signal reg1 : reg
    :=(("00000000000000000000000000000010"), 
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),                                     
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"),
    ("00000000000000000000000000000010"));
    
 
    
signal emptyvect : std_logic_vector(31 downto 0):="00000000000000000000000000000010";
signal rsrc : integer :=0;
signal rsrc1 : integer :=0;
signal rsrc2 : integer :=0;
signal rdest : integer :=0;
signal index : integer :=0;
signal samt : integer:=0;
signal shruti : integer :=1;
signal test : integer :=0;
TYPE state_type is (idle, read, updateir, shiftoper, shiftlefthelper, shiftrighthelper, change);
signal state : state_type :=idle;
signal temp : std_logic_vector(31 downto 0);
signal count: integer :=0;
signal rtype : integer := 0;
signal itype : integer :=0;
signal ifirst : integer := 0;
signal irs : integer := 0;
signal ird : integer :=0;
signal iaddress : integer := 0;
signal iaddress1 : integer :=0;
signal irs1 : integer := 0;
signal ird1 : integer := 0;
signal shamt : integer := 0;
signal funct : integer := 0;
begin

process(clk, state)
    begin
    reg1(19) <= "00000000000000000000000000000111"; --7 is $s3 (address of memory)
    mem1(11) <= "00000000000000000000000000001111"; --15
    mem1(0) <= "00000010010010000100000000100000";  --add$s1,$s2,$s3
--    mem1(2) <= "101011(43) 10011(19) 10001(17) 0000000000001100(12)";
    mem1(2) <= "10101110011100010000000000001100"; --sw $s1, 12($s3)
--    mem1(1) <= "100011(35) 10011(19) 10001(17) 0000000000010000(16)";
--    mem1(1) <= "10001110011100010000000001100100"; --lw $s1,16($s3)
        mem1(1) <= "10001110011100010000000000010000";
--            mem1(3) <= "000000(0) 00000(0) 00001(1) 00001(1) 00100(4) 000000(0)";
        mem1(3) <= "00000000000000010000100100000000"; --sll reg1 by 4 bit
--        mem1(4) <= "000000(0) 00000(0) 00001(1) 00001(1) 00010(2) 000010(2)";
        mem1(4) <= "00000000000000010000100010000010";
    if (clk'EVENT and count<1000) then
--           temp<=mem1(0);
           case state is
                when idle =>
                    itype<=0;
                    rtype<=0;
                    if(count<5) then
                        temp<=mem1(count);
                        else temp<=mem1(0);
                        end if;                                       
                        state <= read;
                when read =>
                count <= count+1; 
                    if(temp(31 downto 26)="000000") then --R type
                        rsrc1<=to_integer(unsigned(temp(25 downto 21)));
                        rsrc2<=to_integer(unsigned(temp(20 downto 16)));
                        rdest<=to_integer(unsigned(temp(15 downto 11)));
                        shamt <= to_integer(unsigned(temp(10 downto 6)));
                        funct <= to_integer(unsigned(temp(5 downto 0)));
                        rtype <= 1;
                        itype<= 0;
                        if(to_integer(unsigned(temp(10 downto 6))) /= 0) then --shamt is not zero, shift operation
                            state<= shiftoper;
                        else
                        state <= change;
                        end if;
                else  --I type
                    itype <= 1;
                    rtype <= 0;
                    ifirst<= to_integer(unsigned(temp(31 downto 26)));
                    irs <= to_integer(unsigned(temp(25 downto 21)));
                    ird <= to_integer(unsigned(temp(20 downto 16)));
                    iaddress1 <= to_integer(unsigned(temp(15 downto 0)))/4;
                    state <= updateir;
--                    state <= change;
                end if;  
                when updateir =>
                        if(ifirst = 35) then
                            irs1 <= (to_integer(unsigned(reg1(irs)))+iaddress1);
                        elsif (ifirst = 43) then
                            irs1 <= to_integer(unsigned(reg1(irs))) + iaddress1;
                        end if;
                            state<= change;
                            
                when shiftoper =>
                        if(funct = 0 and rsrc1 = 0) then --shift left
                            state <= shiftlefthelper;
                        elsif( funct = 2) then
                            state <= shiftrighthelper;
                        else state <= idle;
                        end if;
                        
                when shiftlefthelper =>
                               reg1(rdest) <= reg1(rsrc2)(30 downto 0) & "0";
                               shamt <= shamt-1;
                               if(shamt>0) then
                                    state <= shiftlefthelper;
                                else state <= idle;
                                end if;

                when shiftrighthelper =>
                               reg1(rdest) <= "0" & reg1(rsrc2)(31 downto 1);
                               
                               if(shamt>0) then
                                    shamt <= shamt-1;
                                    state <= shiftrighthelper;
                                else state <= idle;
                                end if;
                
                when change =>
                        if(rtype = 1) then
                            if(temp(5 downto 0)="100000") then --add
                                test<=rdest;
                    --test <= to_integer(unsigned(reg1(rsrc1))+unsigned(reg1(rsrc2)));
                            reg1(rdest)<=std_logic_vector(unsigned(reg1(rsrc1))+unsigned(reg1(rsrc2)));
                            state <= idle;    
                    elsif(temp(5 downto 0)="100010") then --sub
                        reg1(rdest)<=std_logic_vector(unsigned(reg1(rsrc1)) - unsigned(reg1(rsrc2)));
                        state <= idle;
                        end if;
                      elsif (itype = 1) then    --R type
                        if(ifirst = 35) then --lw
                        
                            reg1(ird)<=mem1(irs1);
                            state <=idle;
                        elsif (ifirst = 43) then --sw
                            
                            mem1(irs1)<=reg1(ird);
                            state <= idle;
                            end if;
                         end if;
                         
                    state <= idle;
                         
                    
end case;
end if;
end process;
end Behavioral;

