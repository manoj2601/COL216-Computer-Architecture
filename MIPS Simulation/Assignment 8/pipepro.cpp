
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <iterator>
using namespace std;
//question ki agar memory me add jo ki abhi wb me gya ho aur abhi just ex me koi subt //aaya ho why we didn't considered it as a hazard.
//Maybe because in the same clock cycle we can write in the first half of the clock and
//write in the next half

int register_address(string s)
{
if (s.compare("$zero")==0) {return 0;}
else if(s.compare("$at")==0) {return 1;}
else if(s.compare("$v0")==0) {return 2;}
else if(s.compare("$v1")==0) {return 3;}
else if(s.compare("$a0")==0) {return 4;}
else if(s.compare("$a1")==0) {return 5;}
else if(s.compare("$a2")==0) {return 6;}
else if(s.compare("$a3")==0) {return 7;}
else if(s.compare("$t0")==0) {return 8;}
else if(s.compare("$t1")==0) {return 9;}
else if(s.compare("$t2")==0) {return 10;}
else if(s.compare("$t3")==0) {return 11;}
else if(s.compare("$t4")==0) {return 12;}
else if(s.compare("$t5")==0) {return 13;}
else if(s.compare("$t6")==0) {return 14;}
else if(s.compare("$t7")==0) {return 15;}
else if(s.compare("$s0")==0) {return 16;}
else if(s.compare("$s1")==0) {return 17;}
else if(s.compare("$s2")==0) {return 18;}
else if(s.compare("$s3")==0) {return 19;}
else if(s.compare("$s4")==0) {return 20;}
else if(s.compare("$s5")==0) {return 21;}
else if(s.compare("$s6")==0) {return 22;}
else if(s.compare("$s7")==0) {return 23;}
else if(s.compare("$t8")==0) {return 24;}
else if(s.compare("$t9")==0) {return 25;}
else if(s.compare("$k0")==0) {return 26;}
else if(s.compare("$k1")==0) {return 27;}
else if(s.compare("$gp")==0) {return 28;}
else if(s.compare("$sp")==0) {return 29;}
else if(s.compare("$fp")==0) {return 30;}
else if(s.compare("$ra")==0) {return 31;}
else {return -1;}
}

typedef struct InstrFetch{
   string instr;
   int pc;
}IFstruct;

typedef struct InstrDecode{
   string instr;
   int pc;
   string type_instruction;
   int reg1_index;
   int reg2_index;
   int dest_index;
   int offset;
   int branchtarget; //hum isi me check kr lenge ki ky krna hai
   string label; //for beq, bne , blez, bgtz purpose
}IDstruct;

typedef struct InstrExecute{
  string instr;
  int pc;
  string type_instruction;
  int aluresult;  //isme add subtarct ke results hai, aur all arl ke bhi multiplied value shai
  int swdata; //isme register ki vo value hai jo last me memory me likhni hai
  int branchtarget;  //ye basically program counter ki vo nayi value hai
  int dest_memory;    //add krna h offset ke saath ..matlab isme sirf vo memory ka index mila hai, jisme read ya write krna hai
                   //ye memory ka vo index bhi ho skta hai jis sey read kr rhe ya ya jisme write kr rhe hai
  int dest_register; //ye vo register hai jisme write krna hai
}EXstruct;

typedef struct ReadMemory{
  string instr;
  int pc;
  string type_instruction;
  int dest_register; //memory ka address, register ka index
  int dest_memory;
  int writedata; //vo cheez bhi aayegi jo memory read kri hai, isme aluresult , isme branchtarget bhi aayega, aur jo memory me store krni hai vo bhi
}MEMstruct;

typedef struct WriteBack{
  string instr;
  int pc;
  string type_instruction;
  int dest_register; //memory ka address, register ka index
  int dest_memory;
  int writedata; //vo cheez bhi aayegi jo memory read kri hai, isme aluresult , isme branchtarget bhi aayega
}WBstruct;

string regIndexToString(int a)
{
	switch(a)
	{
		case 0 : return "$zero";
		case 1 : return "$at";
		case 2 : return "$v0";
		case 3 : return "$v1";
		case 4 : return "$a0";
		case 5 : return "$a1";
		case 6 : return "$a2";
		case 7 : return "$a3";
		case 8 : return "$t0";
		case 9 : return "$t1";
		case 10 : return "$t2";
		case 11 : return "$t3";
		case 12 : return "$t4";
		case 13: return "$t5";
		case 14: return "$t6";
		case 15: return "$t7";
		case 16: return "$s0";
		case 17: return "$s1";
		case 18: return "$s2";
		case 19: return "$s3";
		case 20: return "$s4";
		case 21: return "$s5";
		case 22: return "$s6";
		case 23: return "$s7";
		case 24: return "$t8";
		case 25: return "$t9";
		case 26: return "$k0";
		case 27: return "$k1";
		case 28: return "$gp";
		case 29: return "$sp";
		case 30: return "$fb";
		case 31: return "$ra";
		default : return "noop";
	}
}

void printregisters(int registers[]){
	for(int i=0; i<32; i++)
		cout<<regIndexToString(i)<<" : "<<registers[i]<<"\t";
	cout<<endl<<endl;
}
void printmemory(string memory[] , int size){
	for(int i=30; i<size; i++)
	{
		if(memory[i] != "")
			cout<<"memory["<<i<<"] : "<<memory[i]<<endl;
	}
}

int main(){
     int registers[32] = {0};
     string memory[100];
   
   // FOR Test Case 1
    // registers[register_address("$t1")] = 1;
    // registers[register_address("$t2")] = 2;
    // registers[register_address("$t3")] = 3;
    // registers[register_address("$t4")] = 4;
    // registers[register_address("$t5")] = 5;
    // registers[register_address("$ra")] = 50; 
    
    // For Test Case 2
    registers[3] = 4; //v1
    registers[4] = 7; //a0
    registers[5] = 1; //a1
    registers[7] = 3; //a3
    registers[9] = 5; //t1
    registers[10] = 3; //t2
    registers[12] = 2; //t4
    registers[13] = 2; //t5
    registers[14] = 13; //t6
         memory[28] = "73";


     // FOR Test case 3
  //    registers[register_address("$a0")] = 7; //fibonacci number
  //    registers[register_address("$t1")] = 3;
  //    registers[register_address("$t3")] = 2;
  //    registers[register_address("$t4")] = 1;
	 // registers[register_address("$sp")] = 90;
     int program_counter = 0;
     map<string,int> labels;
     int cycles = 0;
     int totalins = 0;
    
    ofstream outfile;
    outfile.open("eachCycleStageReport.txt");
    ofstream outfile2;
    outfile2.open("eachCycleRegisterReport.txt");
    ifstream infile;
    infile.open("instructions.txt"); //opening txt file from where we want to take inputs
    string s;
    int currentinstruction = 0;

    while(getline(infile, s))    //s is the current line which is going to be read
    {
    	// cout<<s<<endl;
        if(s[s.length()-1] ==':') //it is a label
        {
         labels[s.substr(0, s.length()-1)] = currentinstruction;
        //isme current intruction ko nhi increase kiya
        }
        else if(s.length() != 0)
        {
        memory[currentinstruction++] = s;
        //vo label nhi hai to use memory me daal diya hai
        }
    }
    infile.close();
    
   // cout << "labels file\n";
//    map<string,int>::iterator it;
//    for (it = labels.begin(); it != labels.end() ; it++){
//        cout << it->first << "\n" ;
    // cout<<"EHHH";
    IFstruct IF = {"NOOP 0 0 0" , 0};
    IDstruct ID = {"NOOP 0 0 0" , -1, "NOOP" , -1, -1 , -1, -1 , -1 , "blank"};
    EXstruct EX = {"NOOP 0 0 0" , -1, "NOOP", -1, -1, -1 ,-1, -1};
    MEMstruct MEM = {"NOOP 0 0 0" , -1, "NOOP", -1, -1, -1};
    WBstruct WB = {"NOOP 0 0 0" , -1, "NOOP", -1, -1, -1 };
    int totalcycles=0;
    while(1){
    	// string str;
   // exit(1);
    	// cin>>str;
    	outfile<<"IF : "<<IF.pc<<" ID : "<<ID.instr<<" EX : "<<EX.instr<<" MEM : "<<MEM.instr<<" WB : "<<WB.instr<<endl;
        //storing data to eachCycleRegisterReport.txt
		for(int i=0; i<32; i++)
				outfile2<<regIndexToString(i)<<" : "<<registers[i]<<"\t";
			outfile2<<endl;


        if(MEM.type_instruction == "HALT"){
        	cout<<"\ntotal cycles : "<<totalcycles<<endl;
        	cout << "\nreg: " ;
                printregisters(registers);
                cout << "mem: " ;
                printmemory(memory, 100);
            exit(0);
        }
        else{
            //WRITE BACK KA START
            totalcycles++;
            WB.instr = MEM.instr ;
            WB.pc = MEM.pc ;
            WB.type_instruction = MEM.type_instruction ;
            
            if(WB.type_instruction == "NOOP"){
                // cout << "reg: " ;
                // printregisters(registers);
                // cout << "mem: " ;
                // printmemory(memory , 100);
            }
            else if(WB.type_instruction == "ADD"){
                WB.writedata = MEM.writedata ;
                WB.dest_register = MEM.dest_register ;
                registers[WB.dest_register] = WB.writedata ;
            }
            else if(WB.type_instruction == "SUB"){
                WB.writedata = MEM.writedata ;
                WB.dest_register = MEM.dest_register ;
                registers[WB.dest_register] = WB.writedata ;
            }
            else if(WB.type_instruction == "SLL"){
                WB.writedata = MEM.writedata ;
                WB.dest_register = MEM.dest_register ;
                registers[WB.dest_register] = WB.writedata ;
            }
            else if(WB.type_instruction == "SRL"){
                WB.writedata = MEM.writedata ;
                WB.dest_register = MEM.dest_register ;
                registers[WB.dest_register] = WB.writedata ;
            }
            else if(WB.type_instruction == "LW"){
                WB.writedata = MEM.writedata ;
                WB.dest_register = MEM.dest_register ;
                registers[WB.dest_register] = WB.writedata ;
            }
            else if(WB.type_instruction == "SW"){
                WB.writedata = MEM.writedata ;
                  WB.dest_memory = MEM.dest_memory;

                  // stringstream str1;
                  // str1 << WB.writedata ;
                  // string s = str1.str();
                
                  // memory[WB.dest_memory] = s;
            }

            
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     //READ MEMORY KA START
            
            MEM.instr = EX.instr;
            MEM.pc = EX.pc;
            MEM.type_instruction = EX.type_instruction;
              
            if(MEM.type_instruction == "NOOP"){
                
            }
            else if(MEM.type_instruction == "ADD"){
                MEM.dest_register = EX.dest_register ;
                MEM.writedata = EX.aluresult ;
            }
            else if(MEM.type_instruction == "SUB"){
                MEM.dest_register = EX.dest_register ;
                MEM.writedata = EX.aluresult ;
            }
            else if(MEM.type_instruction == "SLL"){
                MEM.dest_register = EX.dest_register ;
                MEM.writedata = EX.aluresult ;
            }
            else if(MEM.type_instruction == "SRL"){
                MEM.dest_register = EX.dest_register ;
                MEM.writedata = EX.aluresult ;
            }
            else if(MEM.type_instruction == "LW"){
                MEM.dest_register = EX.dest_register ;
                MEM.dest_memory = EX.dest_memory ;
                stringstream str(memory[MEM.dest_memory]);
                int v;
                str >> v;
                MEM.writedata = v ;
            }
            else if(MEM.type_instruction == "SW"){
                MEM.dest_memory = EX.dest_memory ;
                MEM.writedata = EX.swdata ;
                  WB.writedata = MEM.writedata ;
                  WB.dest_memory = MEM.dest_memory;

                  stringstream str1;
                  str1 << MEM.writedata ;
                  string s = str1.str();
                
                  memory[MEM.dest_memory] = s;
            }
        
                
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Instruction execute ka start
           
            if(EX.type_instruction == "NOOP"||
               EX.type_instruction=="Jumpstall"||
               EX.type_instruction=="J"||EX.type_instruction=="JAL"||EX.type_instruction=="JR"||
               EX.type_instruction=="BranchStall"||EX.type_instruction == "BranchHazard"||
               EX.type_instruction=="BEQ"||EX.type_instruction=="BNE"||EX.type_instruction=="BLEZ"||EX.type_instruction=="BGTZ")
            {
                EX.instr = ID.instr;
                EX.pc = ID.pc;
                EX.type_instruction = ID.type_instruction;
                
                    if(EX.type_instruction == "ADD"){
                        EX.dest_register = ID.dest_index;
                        EX.aluresult = registers[ID.reg1_index] + registers[ID.reg2_index] ;
                    }
                    else if(EX.type_instruction == "SUB"){
                        EX.dest_register = ID.dest_index;
                        EX.aluresult = registers[ID.reg1_index] - registers[ID.reg2_index] ;
                    }
                    else if(EX.type_instruction == "SLL"){
                        EX.dest_register = ID.dest_index;
                        int value = registers[ID.reg1_index];
                        int c = ID.offset;
                        for (int k = 0 ; k < c ; k++ ) { value = value * 2; }
                        EX.aluresult = value;
                    }
                    else if(EX.type_instruction == "SRL"){
                        EX.dest_register = ID.dest_index;
                        int value = registers[ID.reg1_index];
                        int c = ID.offset;
                        int two = 1;
                        for (int h = 0 ; h < c ; h++) { two = two * 2;}
                        value = (int) (value/two);
                        EX.aluresult = value ;
                    }
                    else if(EX.type_instruction == "LW"){
                        EX.dest_register = ID.dest_index;
                        EX.dest_memory  =  (ID.offset + registers[ID.reg1_index]) ;
                    }
                    else if(EX.type_instruction == "SW"){
                        EX.swdata = registers[ID.dest_index];
                        EX.dest_memory  =  (ID.offset + registers[ID.reg1_index]) ;
                    }
                    else if(EX.type_instruction == "BEQ"){       //MEM me abhi noop hai
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                           ||WB.type_instruction=="LW")
                        {
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else if(WB.dest_register == ID.reg2_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(registers[ID.reg1_index] == registers[ID.reg2_index]){
                                 ID.instr = "BranchStall 0 0 0";
                                 ID.type_instruction = "BranchStall";
                                 IF.instr = "BranchStall 0 0 0";
                                 IF.pc = labels[ID.label];
                                 continue;
                              }
                           }
                        }
                        else{
                        if(registers[ID.reg1_index] == registers[ID.reg2_index]){
                            ID.instr = "BranchStall 0 0 0";
                            ID.type_instruction = "BranchStall";
                            IF.instr = "BranchStall 0 0 0";
                            IF.pc = labels[ID.label];
                            continue;
                        }
                       }
                    }
                    else if(EX.type_instruction == "BNE"){       //MEM me abhi noop hai
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                           ||WB.type_instruction=="LW")
                        {
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else if(WB.dest_register == ID.reg2_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(registers[ID.reg1_index] != registers[ID.reg2_index]){
                                 ID.instr = "BranchStall 0 0 0";
                                 ID.type_instruction = "BranchStall";
                                 IF.instr = "BranchStall 0 0 0";
                                 IF.pc = labels[ID.label];
                                 continue;
                              }
                           }
                        }
                        else{
                        if(registers[ID.reg1_index] != registers[ID.reg2_index]){
                            ID.instr = "BranchStall 0 0 0";
                            ID.type_instruction = "BranchStall";
                            IF.instr = "BranchStall 0 0 0";
                            IF.pc = labels[ID.label];
                            continue;
                        }
                       }
                    }
                    else if(EX.type_instruction == "BGTZ"){
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                           ||WB.type_instruction=="LW"){
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(registers[ID.reg1_index] > 0){
                                    ID.instr = "BranchStall 0 0 0";
                                    ID.type_instruction = "BranchStall";
                                    IF.instr = "BranchStall 0 0 0";
                                    IF.pc = labels[ID.label];
                                    continue;
                                }
                             }
                        }
                        else{
                            if(registers[ID.reg1_index] > 0){
                                ID.instr = "BranchStall 0 0 0";
                                ID.type_instruction = "BranchStall";
                                IF.instr = "BranchStall 0 0 0";
                                IF.pc = labels[ID.label];
                                continue;
                            }
                        }
                    }
                    else if(EX.type_instruction == "BLEZ"){
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                           ||WB.type_instruction=="LW"){
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(registers[ID.reg1_index] <= 0){
                                    ID.instr = "BranchStall 0 0 0";
                                    ID.type_instruction = "BranchStall";
                                    IF.instr = "BranchStall 0 0 0";
                                    IF.pc = labels[ID.label];
                                    continue;
                                }
                             }
                        }
                        else{
                            if(registers[ID.reg1_index] <= 0){
                                ID.instr = "BranchStall 0 0 0";
                                ID.type_instruction = "BranchStall";
                                IF.instr = "BranchStall 0 0 0";
                                IF.pc = labels[ID.label];
                                continue;
                            }
                        }
                    }
            }
            else if(EX.type_instruction=="ADD"||EX.type_instruction=="SUB"||EX.type_instruction=="SLL"||EX.type_instruction=="SRL"||
                    EX.type_instruction=="LW"){
                EX.instr = ID.instr;
                EX.pc = ID.pc;
                EX.type_instruction = ID.type_instruction;
                    if(EX.type_instruction == "ADD"){
                        if(EX.dest_register == ID.reg1_index){
                             EX.instr = "STALL_datahaz_1st 0 0 0" ;
                             EX.type_instruction = "STALL_datahaz_1st" ;
                            continue;
                        }
                        else if(EX.dest_register == ID.reg2_index){
                             EX.instr = "STALL_datahaz_1st 0 0 0" ;
                             EX.type_instruction = "STALL_datahaz_1st" ;
                            continue;
                        }
                        else{
                             EX.dest_register = ID.dest_index;
                             EX.aluresult = registers[ID.reg1_index] + registers[ID.reg2_index] ;
                        }
                    }
                    else if(EX.type_instruction == "SUB"){
                        if(EX.dest_register == ID.reg1_index){
                            EX.instr = "STALL_datahaz_1st 0 0 0" ;
                            EX.type_instruction = "STALL_datahaz_1st" ;
                            continue;
                        }
                        else if(EX.dest_register == ID.reg2_index){
                            EX.instr = "STALL_datahaz_1st 0 0 0" ;
                            EX.type_instruction = "STALL_datahaz_1st" ;
                            continue;
                        }
                        else{
                            EX.dest_register = ID.dest_index;
                            EX.aluresult = registers[ID.reg1_index] - registers[ID.reg2_index] ;
                        }
                    }
                    else if(EX.type_instruction == "SLL"){
                        if(EX.dest_register == ID.reg1_index){
                            EX.instr = "STALL_datahaz_1st 0 0 0" ;
                            EX.type_instruction = "STALL_datahaz_1st" ;
                            continue;
                        }
                        else{
                            EX.dest_register = ID.dest_index;
                            int value = registers[ID.reg1_index];
                            int c = ID.offset;
                            for (int k = 0 ; k < c ; k++ ) { value = value * 2; }
                            EX.aluresult = value;
                        }
                    }
                    else if(EX.type_instruction == "SRL"){
                        if(EX.dest_register == ID.reg1_index){
                            EX.instr = "STALL_datahaz_1st 0 0 0" ;
                            EX.type_instruction = "STALL_datahaz_1st" ;
                            continue;
                        }
                        else{
                            EX.dest_register = ID.dest_index;
                            int value = registers[ID.reg1_index];
                            int c = ID.offset;
                            int two = 1;
                            for (int h = 0 ; h < c ; h++) { two = two * 2;}
                            value = (int) (value/two);
                            EX.aluresult = value ;
                        }
                    }
                    else if(EX.type_instruction == "LW"){
                        if(EX.dest_register == ID.reg1_index){
                            EX.instr = "STALL_datahaz_1st 0 0 0" ;
                            EX.type_instruction = "STALL_datahaz_1st" ;
                            continue;
                        }
                        else{
                            EX.dest_register = ID.dest_index;
                            EX.dest_memory  =  (ID.offset + registers[ID.reg1_index]) ;
                        }
                    }
                    else if(EX.type_instruction == "SW"){
                        if(EX.dest_register == ID.dest_index){
                            EX.instr = "STALL_datahaz_1st 0 0 0" ;
                            EX.type_instruction = "STALL_datahaz_1st" ;
                            continue;
                        }
                        else if(EX.dest_register == ID.reg1_index){
                            EX.instr = "STALL_datahaz_1st 0 0 0" ;
                            EX.type_instruction = "STALL_datahaz_1st" ;
                            continue;
                        }
                        else{
                            EX.swdata = registers[ID.dest_index];
                            EX.dest_memory  =  (ID.offset + registers[ID.reg1_index]) ;
                        }
                    }
                    else if(EX.type_instruction == "BEQ"){//isme MEM me kuch add sub sll srl lw type ki cheeze hain
                        
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                        ||WB.type_instruction=="LW"){
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else if(WB.dest_register == ID.reg2_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(EX.dest_register == ID.reg1_index){
                                    EX.instr = "BranchHazard 0 0 0";
                                    EX.type_instruction = "BranchHazard";
                                    continue;
                                }
                                else if(EX.dest_register == ID.reg2_index){
                                    EX.instr = "BranchHazard 0 0 0";
                                    EX.type_instruction = "BranchHazard";
                                    continue;
                                }
                                else{  //kisi ke bhi equal nahin hai
                                    if(registers[ID.reg1_index] == registers[ID.reg2_index]){
                                        ID.instr = "BranchStall 0 0 0";
                                        ID.type_instruction = "BranchStall";
                                        IF.instr = "BranchStall 0 0 0";
                                        IF.pc = labels[ID.label];
                                        continue;
                                    }
                                }
                            }
                        }
                        else{
                            if(EX.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else if(EX.dest_register == ID.reg2_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{  //kisi ke bhi equal nahin hai
                                if(registers[ID.reg1_index] == registers[ID.reg2_index]){
                                    ID.instr = "BranchStall 0 0 0";
                                    ID.type_instruction = "BranchStall";
                                    IF.instr = "BranchStall 0 0 0";
                                    IF.pc = labels[ID.label];
                                    continue;
                                }
                            }
                        }
                    }
                    else if(EX.type_instruction == "BNE"){//isme MEM me kuch add sub sll srl lw type ki cheeze hain
                        
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                        ||WB.type_instruction=="LW"){
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else if(WB.dest_register == ID.reg2_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(EX.dest_register == ID.reg1_index){
                                    EX.instr = "BranchHazard 0 0 0";
                                    EX.type_instruction = "BranchHazard";
                                    continue;
                                }
                                else if(EX.dest_register == ID.reg2_index){
                                    EX.instr = "BranchHazard 0 0 0";
                                    EX.type_instruction = "BranchHazard";
                                    continue;
                                }
                                else{  //kisi ke bhi equal nahin hai
                                    if(registers[ID.reg1_index] != registers[ID.reg2_index]){
                                        ID.instr = "BranchStall 0 0 0";
                                        ID.type_instruction = "BranchStall";
                                        IF.instr = "BranchStall 0 0 0";
                                        IF.pc = labels[ID.label];
                                        continue;
                                    }
                                }
                            }
                        }
                        else{
                            if(EX.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else if(EX.dest_register == ID.reg2_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{  //kisi ke bhi equal nahin hai
                                if(registers[ID.reg1_index] != registers[ID.reg2_index]){
                                    ID.instr = "BranchStall 0 0 0";
                                    ID.type_instruction = "BranchStall";
                                    IF.instr = "BranchStall 0 0 0";
                                    IF.pc = labels[ID.label];
                                    continue;
                                }
                            }
                        }
                    }
                    else if(EX.type_instruction == "BGTZ"){//isme MEM me kuch add sub sll srl lw type ki cheeze hain
                        
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                        ||WB.type_instruction=="LW"){
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(EX.dest_register == ID.reg1_index){
                                    EX.instr = "BranchHazard 0 0 0";
                                    EX.type_instruction = "BranchHazard";
                                    continue;
                                }
                                else{  //kisi ke bhi equal nahin hai
                                    if(registers[ID.reg1_index] > 0){
                                        ID.instr = "BranchStall 0 0 0";
                                        ID.type_instruction = "BranchStall";
                                        IF.instr = "BranchStall 0 0 0";
                                        IF.pc = labels[ID.label];
                                        continue;
                                    }
                                }
                            }
                        }
                        else{
                            if(EX.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{  //kisi ke bhi equal nahin hai
                                if(registers[ID.reg1_index] > 0){
                                    ID.instr = "BranchStall 0 0 0";
                                    ID.type_instruction = "BranchStall";
                                    IF.instr = "BranchStall 0 0 0";
                                    IF.pc = labels[ID.label];
                                    continue;
                                }
                            }
                        }
                    }
                    else if(EX.type_instruction == "BLEZ"){//isme MEM me kuch add sub sll srl lw type ki cheeze hain
                        
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                        ||WB.type_instruction=="LW"){
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(EX.dest_register == ID.reg1_index){
                                    EX.instr = "BranchHazard 0 0 0";
                                    EX.type_instruction = "BranchHazard";
                                    continue;
                                }
                                else{  //kisi ke bhi equal nahin hai
                                    if(registers[ID.reg1_index] <= 0){
                                        ID.instr = "BranchStall 0 0 0";
                                        ID.type_instruction = "BranchStall";
                                        IF.instr = "BranchStall 0 0 0";
                                        IF.pc = labels[ID.label];
                                        continue;
                                    }
                                }
                            }
                        }
                        else{
                            if(EX.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{  //kisi ke bhi equal nahin hai
                                if(registers[ID.reg1_index] <= 0){
                                    ID.instr = "BranchStall 0 0 0";
                                    ID.type_instruction = "BranchStall";
                                    IF.instr = "BranchStall 0 0 0";
                                    IF.pc = labels[ID.label];
                                    continue;
                                }
                            }
                        }
                    }
            }
            else if(EX.type_instruction == "SW"){
                if(ID.type_instruction == "NOOP"){
                    EX.instr = ID.instr;
                    EX.pc = ID.pc;
                    EX.type_instruction = ID.type_instruction;
                }
                else if(ID.type_instruction == "ADD"){
                    EX.instr = ID.instr;
                    EX.pc = ID.pc;
                    EX.type_instruction = ID.type_instruction;
                    EX.dest_register = ID.dest_index;
                    EX.aluresult = registers[ID.reg1_index] + registers[ID.reg2_index] ;
                }
                else if(ID.type_instruction == "SUB"){
                    EX.instr = ID.instr;
                    EX.pc = ID.pc;
                    EX.type_instruction = ID.type_instruction;
                    EX.dest_register = ID.dest_index;
                    EX.aluresult = registers[ID.reg1_index] - registers[ID.reg2_index] ;
                }
                else if(ID.type_instruction == "SLL"){
                    EX.instr = ID.instr;
                    EX.pc = ID.pc;
                    EX.type_instruction = ID.type_instruction;
                    EX.dest_register = ID.dest_index;
                    int value = registers[ID.reg1_index];
                    int c = ID.offset;
                    for (int k = 0 ; k < c ; k++ ){ value = value * 2;}
                    EX.aluresult = value;
                }
                else if(ID.type_instruction == "SRL"){
                    EX.instr = ID.instr;
                    EX.pc = ID.pc;
                    EX.type_instruction = ID.type_instruction;
                    EX.dest_register = ID.dest_index;
                    int value = registers[ID.reg1_index];
                    int c = ID.offset;
                    int two = 1;
                    for (int h = 0 ; h < c ; h++) {two = two * 2;}
                    value = (int) (value/two);
                    EX.aluresult = value ;
                }
                else if(ID.type_instruction == "LW"){
                            EX.instr = ID.instr;
                            EX.pc = ID.pc;
                            EX.type_instruction = ID.type_instruction;
                            EX.dest_register = ID.dest_index;
                            EX.dest_memory  =  (ID.offset + registers[ID.reg1_index]);
                    // EX.instr = "STALL_structuralhaz 0 0 0" ;
                    //  EX.type_instruction = "STALL_structuralhaz";
                    // continue;
                }
                else if(ID.type_instruction == "SW"){
                    EX.instr = ID.instr;
                    EX.pc = ID.pc;
                    EX.type_instruction = ID.type_instruction;
                    EX.swdata = registers[ID.dest_index];
                    EX.dest_memory  =  (ID.offset + registers[ID.reg1_index]) ;
                }
                else if(EX.type_instruction == "BEQ"){       //MEM me abhi noop hai
                    if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                       ||WB.type_instruction=="LW")
                    {
                        if(WB.dest_register == ID.reg1_index){
                            EX.instr = "BranchHazard 0 0 0";
                            EX.type_instruction = "BranchHazard";
                            continue;
                        }
                        else if(WB.dest_register == ID.reg2_index){
                            EX.instr = "BranchHazard 0 0 0";
                            EX.type_instruction = "BranchHazard";
                            continue;
                        }
                        else{
                            if(registers[ID.reg1_index] == registers[ID.reg2_index]){
                             ID.instr = "BranchStall 0 0 0";
                             ID.type_instruction = "BranchStall";
                             IF.instr = "BranchStall 0 0 0";
                             IF.pc = labels[ID.label];
                             continue;
                          }
                       }
                    }
                    else{
                    if(registers[ID.reg1_index] == registers[ID.reg2_index]){
                        ID.instr = "BranchStall 0 0 0";
                        ID.type_instruction = "BranchStall";
                        IF.instr = "BranchStall 0 0 0";
                        IF.pc = labels[ID.label];
                        continue;
                    }
                   }
                }
                else if(EX.type_instruction == "BNE"){       //MEM me abhi noop hai
                    if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                       ||WB.type_instruction=="LW")
                    {
                        if(WB.dest_register == ID.reg1_index){
                            EX.instr = "BranchHazard 0 0 0";
                            EX.type_instruction = "BranchHazard";
                            continue;
                        }
                        else if(WB.dest_register == ID.reg2_index){
                            EX.instr = "BranchHazard 0 0 0";
                            EX.type_instruction = "BranchHazard";
                            continue;
                        }
                        else{
                            if(registers[ID.reg1_index] != registers[ID.reg2_index]){
                             ID.instr = "BranchStall 0 0 0";
                             ID.type_instruction = "BranchStall";
                             IF.instr = "BranchStall 0 0 0";
                             IF.pc = labels[ID.label];
                             continue;
                          }
                       }
                    }
                    else{
                    if(registers[ID.reg1_index] != registers[ID.reg2_index]){
                        ID.instr = "BranchStall 0 0 0";
                        ID.type_instruction = "BranchStall";
                        IF.instr = "BranchStall 0 0 0";
                        IF.pc = labels[ID.label];
                        continue;
                    }
                   }
                }
                else if(EX.type_instruction == "BGTZ"){
                    if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                       ||WB.type_instruction=="LW"){
                        if(WB.dest_register == ID.reg1_index){
                            EX.instr = "BranchHazard 0 0 0";
                            EX.type_instruction = "BranchHazard";
                            continue;
                        }
                        else{
                            if(registers[ID.reg1_index] > 0){
                                ID.instr = "BranchStall 0 0 0";
                                ID.type_instruction = "BranchStall";
                                IF.instr = "BranchStall 0 0 0";
                                IF.pc = labels[ID.label];
                                continue;
                            }
                         }
                    }
                    else{
                        if(registers[ID.reg1_index] > 0){
                            ID.instr = "BranchStall 0 0 0";
                            ID.type_instruction = "BranchStall";
                            IF.instr = "BranchStall 0 0 0";
                            IF.pc = labels[ID.label];
                            continue;
                        }
                    }
                }
                else if(EX.type_instruction == "BLEZ"){
                    if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                       ||WB.type_instruction=="LW"){
                        if(WB.dest_register == ID.reg1_index){
                            EX.instr = "BranchHazard 0 0 0";
                            EX.type_instruction = "BranchHazard";
                            continue;
                        }
                        else{
                            if(registers[ID.reg1_index] <= 0){
                                ID.instr = "BranchStall 0 0 0";
                                ID.type_instruction = "BranchStall";
                                IF.instr = "BranchStall 0 0 0";
                                IF.pc = labels[ID.label];
                                continue;
                            }
                         }
                    }
                    else{
                        if(registers[ID.reg1_index] <= 0){
                            ID.instr = "BranchStall 0 0 0";
                            ID.type_instruction = "BranchStall";
                            IF.instr = "BranchStall 0 0 0";
                            IF.pc = labels[ID.label];
                            continue;
                        }
                    }
                }
            }
            else if(EX.type_instruction == "STALL_datahaz_1st"){
                EX.instr = "STALL_datahaz_2nd 0 0 0";
                EX.type_instruction = "STALL_datahaz_2nd";
                continue;
            }
            else if(EX.type_instruction == "STALL_datahaz_2nd"){
                EX.instr = ID.instr;
                EX.pc = ID.pc;
                EX.type_instruction = ID.type_instruction;
                    if(EX.type_instruction == "ADD"){
                        EX.dest_register = ID.dest_index;
                        EX.aluresult = registers[ID.reg1_index] + registers[ID.reg2_index] ;
                    }
                    else if(EX.type_instruction == "SUB"){
                        EX.dest_register = ID.dest_index;
                        EX.aluresult = registers[ID.reg1_index] - registers[ID.reg2_index] ;
                    }
                    else if(EX.type_instruction == "SLL"){
                        EX.dest_register = ID.dest_index;
                        int value = registers[ID.reg1_index];
                        int c = ID.offset;
                        for (int k = 0 ; k < c ; k++ ) { value = value * 2; }
                        EX.aluresult = value;
                    }
                    else if(EX.type_instruction == "SRL"){
                        EX.dest_register = ID.dest_index;
                        int value = registers[ID.reg1_index];
                        int c = ID.offset;
                        int two = 1;
                        for (int h = 0 ; h < c ; h++) { two = two * 2;}
                        value = (int) (value/two);
                        EX.aluresult = value ;
                    }
                    else if(EX.type_instruction == "LW"){
                        EX.dest_register = ID.dest_index;
                        EX.dest_memory  =  (ID.offset + registers[ID.reg1_index]) ;
                    }
                    else if(EX.type_instruction == "SW"){
                        EX.swdata = registers[ID.dest_index];
                        EX.dest_memory  =  (ID.offset + registers[ID.reg1_index]) ;
                    }
                    else if(EX.type_instruction == "BEQ"){       //MEM me abhi noop hai
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                           ||WB.type_instruction=="LW")
                        {
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else if(WB.dest_register == ID.reg2_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(registers[ID.reg1_index] == registers[ID.reg2_index]){
                                 ID.instr = "BranchStall 0 0 0";
                                 ID.type_instruction = "BranchStall";
                                 IF.instr = "BranchStall 0 0 0";
                                 IF.pc = labels[ID.label];
                                 continue;
                              }
                           }
                        }
                        else{
                        if(registers[ID.reg1_index] == registers[ID.reg2_index]){
                            ID.instr = "BranchStall 0 0 0";
                            ID.type_instruction = "BranchStall";
                            IF.instr = "BranchStall 0 0 0";
                            IF.pc = labels[ID.label];
                            continue;
                        }
                       }
                    }
                    else if(EX.type_instruction == "BNE"){       //MEM me abhi noop hai
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                           ||WB.type_instruction=="LW")
                        {
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else if(WB.dest_register == ID.reg2_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(registers[ID.reg1_index] != registers[ID.reg2_index]){
                                 ID.instr = "BranchStall 0 0 0";
                                 ID.type_instruction = "BranchStall";
                                 IF.instr = "BranchStall 0 0 0";
                                 IF.pc = labels[ID.label];
                                 continue;
                              }
                           }
                        }
                        else{
                        if(registers[ID.reg1_index] != registers[ID.reg2_index]){
                            ID.instr = "BranchStall 0 0 0";
                            ID.type_instruction = "BranchStall";
                            IF.instr = "BranchStall 0 0 0";
                            IF.pc = labels[ID.label];
                            continue;
                        }
                       }
                    }
                    else if(EX.type_instruction == "BGTZ"){
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                           ||WB.type_instruction=="LW"){
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(registers[ID.reg1_index] > 0){
                                    ID.instr = "BranchStall 0 0 0";
                                    ID.type_instruction = "BranchStall";
                                    IF.instr = "BranchStall 0 0 0";
                                    IF.pc = labels[ID.label];
                                    continue;
                                }
                             }
                        }
                        else{
                            if(registers[ID.reg1_index] > 0){
                                ID.instr = "BranchStall 0 0 0";
                                ID.type_instruction = "BranchStall";
                                IF.instr = "BranchStall 0 0 0";
                                IF.pc = labels[ID.label];
                                continue;
                            }
                        }
                    }
                    else if(EX.type_instruction == "BLEZ"){
                        if(WB.type_instruction=="ADD"||WB.type_instruction=="SUB"||WB.type_instruction=="SLL"||WB.type_instruction=="SRL"
                           ||WB.type_instruction=="LW"){
                            if(WB.dest_register == ID.reg1_index){
                                EX.instr = "BranchHazard 0 0 0";
                                EX.type_instruction = "BranchHazard";
                                continue;
                            }
                            else{
                                if(registers[ID.reg1_index] <= 0){
                                    ID.instr = "BranchStall 0 0 0";
                                    ID.type_instruction = "BranchStall";
                                    IF.instr = "BranchStall 0 0 0";
                                    IF.pc = labels[ID.label];
                                    continue;
                                }
                             }
                        }
                        else{
                            if(registers[ID.reg1_index] <= 0){
                                ID.instr = "BranchStall 0 0 0";
                                ID.type_instruction = "BranchStall";
                                IF.instr = "BranchStall 0 0 0";
                                IF.pc = labels[ID.label];
                                continue;
                            }
                        }
                    }
            }
            else if(EX.type_instruction == "STALL_structuralhaz"){
                EX.instr = ID.instr;
                EX.pc = ID.pc;
                EX.type_instruction = ID.type_instruction;
                if(EX.type_instruction == "LW"){
                    EX.dest_register = ID.dest_index;
                    EX.dest_memory  =  (ID.offset + registers[ID.reg1_index]) ;
                }
            }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            
            ID.instr = IF.instr;
            ID.pc = IF.pc;
            stringstream sep(ID.instr);
            sep >> ID.type_instruction;
            
            if(ID.type_instruction == "NOOP"){
                
            }
            else if(ID.type_instruction == "ADD"){
                string destreg;
                string reg1;
                string reg2;
                sep >> destreg ;
                sep >> reg1 ;
                sep >> reg2 ;
                ID.dest_index  =  register_address(destreg);
                ID.reg1_index = register_address(reg1);
                ID.reg2_index = register_address(reg2);
            }
            else if(ID.type_instruction == "SUB"){
                string destreg;
                string reg1;
                string reg2;
                sep >> destreg ;
                sep >> reg1 ;
                sep >> reg2 ;
                ID.dest_index  =  register_address(destreg);
                ID.reg1_index = register_address(reg1);
                ID.reg2_index = register_address(reg2);
            }
            else if(ID.type_instruction == "SLL"){
                string destreg;
                sep >> destreg;
                ID.dest_index  =  register_address(destreg);
                string reg1;
                sep >> reg1;
                ID.reg1_index = register_address(reg1);
                string offsetstr;
                sep >> offsetstr;
                stringstream b1(offsetstr);
                int c;
                b1>>c;
                ID.offset = c;
            }
            else if(ID.type_instruction == "SRL"){
                string destreg;
                sep >> destreg;
                ID.dest_index  =  register_address(destreg);
                string reg1;
                sep >> reg1;
                ID.reg1_index = register_address(reg1);
                string offsetstr;
                sep >> offsetstr;
                stringstream b1(offsetstr);
                int c;
                b1>>c;
                ID.offset = c;
            }
            else if(ID.type_instruction == "LW"){
                string destreg;
                sep >> destreg;
                ID.dest_index  =  register_address(destreg);
                
                string offsetreg_str;
                sep >> offsetreg_str;
                int len = offsetreg_str.size();
                int h=0;
                for (int k=0; k<len ; k++){
                    while( offsetreg_str[h] != '(' ){
                        h++;
                    }
                    break;
                }
                string offs = "";
                for (int g=0; g<h ; g++){
                    offs += offsetreg_str[g];
                }
                stringstream b1(offs);
                int b;
                b1 >> b;
                
                string reg = "";
                for (int g=0 ; g< (len-h-2) ; g++){
                    reg += offsetreg_str[g+h+1];
                }
                
                ID.offset = b;
                ID.reg1_index =  register_address(reg);
            }
            else if(ID.type_instruction == "SW"){
                string destreg;
                sep >> destreg;
                ID.dest_index  =  register_address(destreg);
                
                string offsetreg_str;
                sep >> offsetreg_str;
                int len = offsetreg_str.size();
                int h=0;
                for (int k=0; k<len ; k++){
                    while( offsetreg_str[h] != '(' ){
                        h++;
                    }
                    break;
                }
                string offs = "";
                for (int g=0; g<h ; g++){
                    offs += offsetreg_str[g];
                }
                stringstream b1(offs);
                int b;
                b1 >> b;
                
                string reg = "";
                for (int g=0 ; g< (len-h-2) ; g++){
                    reg += offsetreg_str[g+h+1];
                }
                
                ID.offset = b;
                ID.reg1_index =  register_address(reg);
            }
            else if(ID.type_instruction == "BEQ"){
                string reg1;
                string reg2;
                sep >> reg1 >> reg2;
                ID.reg1_index = register_address(reg1);
                ID.reg2_index = register_address(reg2);
                string lab;
                sep >> lab;
                ID.label = lab;
            }
            else if(ID.type_instruction == "BNE"){
                string reg1;
                string reg2;
                sep >> reg1 >> reg2;
                ID.reg1_index = register_address(reg1);
                ID.reg2_index = register_address(reg2);
                string lab;
                sep >> lab;
                ID.label = lab;
            }
            else if(ID.type_instruction == "BGTZ"){
                string reg1;
                sep >> reg1;
                ID.reg1_index = register_address(reg1);
                string lab;
                sep >> lab;
                ID.label = lab;
            }
            else if(ID.type_instruction == "BLEZ"){
                string reg1;
                sep >> reg1;
                ID.reg1_index = register_address(reg1);
                string lab;
                sep >> lab;
                ID.label = lab;
            }
            else if(ID.type_instruction == "J"){
                string lab;
                sep >> lab;
                ID.label = lab;
                int new_pc = labels[ID.label];
                IF.pc = new_pc;
                IF.instr = "Jumpstall 0 0 0";
                continue;
            }
            else if(ID.type_instruction == "JR"){
                string reg;
                sep >> reg;
                int regindex = register_address(reg) ;
                int new_pc = registers[regindex];
                IF.pc = new_pc;
                IF.instr = "Jumpstall 0 0 0";
                continue;
            }
            else if(ID.type_instruction == "JAL"){
                string lab;
                sep >> lab;
                ID.label = lab;
                int new_pc = labels[ID.label];
                registers[31] = ID.pc ;
                IF.pc = new_pc;
                IF.instr = "Jumpstall 0 0 0";
                continue;
            }
            else if(ID.type_instruction == "Jumpstall"){
                
            }
            
            
            
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //INSTRUCTION FETCH KA START
                IF.instr = memory[IF.pc] ;
                IF.pc = IF.pc + 1 ;
        }
        
        }
         
        }

