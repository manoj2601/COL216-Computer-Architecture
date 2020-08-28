#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <iterator>
using namespace std;

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


int main()
{
    int registers[32] = {0};
    string memory[100];
    int program_counter = 0;
    map<string,int> labels; //it is like a hashtable in with key = label(string) and value(uske just aage wala instruction ka index)
//matlab humne labels me labels along with their instruction number daale hain
    map<string,int> time;
    int totaltime=0;
    int totalins = 0;

 ifstream infile;
  infile.open("instructions.txt"); //opening txt file from where we want to take inputs
  string s;
  int currentinstruction = 0;
while(getline(infile, s))    //s is the current line which is going to be read
{
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
ifstream infile2;
infile2.open("input1.txt");

string s1;
    while(getline(infile2, s1))
    {
      stringstream sep(s1);
      string one;
      sep>>one;
      int a;
      sep>>a;
      time[one] = a;
    }
infile2.close();
infile.close();

while(memory[program_counter] != "")	//ith instruction
{
stringstream sep(memory[program_counter]);
string one;
sep >> one;

    if(one == "ADD")
    {
          totaltime += time["ADD"];
          totalins++;
          string reg1, reg2, reg3;
          sep>>reg1;
          sep>>reg2;
          sep>>reg3;
        //execute your add instruction here
        // cin>>instruction_4[0]>>instruction_4[1]>>instruction_4[2]>>instruction_4[3] ;

        int a = register_address(reg1);
        int b = register_address(reg2);
        int c = register_address(reg3);

        registers[a] = registers[b] + registers[c] ;
    }

    else if(one == "SUB")
    {
      totaltime += time["SUB"];
      totalins++;
      //same as above
      string reg1, reg2, reg3;
      sep>>reg1;
      sep>>reg2;
      sep>>reg3;

//execute your add instruction here
// cin>>instruction_4[0]>>instruction_4[1]>>instruction_4[2]>>instruction_4[3] ;

      int a = register_address(reg1);
      int b = register_address(reg2);
      int c = register_address(reg3);

      registers[a] = registers[b] - registers[c] ;
   }

    else if (one == "LW")
    {
        totaltime += time["LW"];
        totalins++;
        // cin>>instruction_3[0]>>instruction_3[1]>>instruction_3[2]
        string instruction_3[3];
        instruction_3[0] = "LW";
        sep>>instruction_3[1];
        sep>>instruction_3[2];
        int a = register_address(instruction_3[1]);

        int memory_len = instruction_3[2].size();
        int h = 0;
        for (int k = 0 ; k < memory_len ; k++){
        if(instruction_3[2][k] != '(')
        {
        h++;
        }
        break;
        }
        string addr = "";
        // char addr[h];
        for (int g = 0 ; g < h ; g++) {
        addr+= instruction_3[2][g];
        }
        string reg = "";
        // char reg[memory_len - h - 2];
        for (int g = 0 ; g< (memory_len - h - 2); g++)
        {
        reg += instruction_3[2][g+h+1];
        }

        // int b = boost::lexical_cast(addr);
        stringstream b1(addr);
        int b;
        b1>>b;

        int k = register_address(reg);
        int c = registers[k];
        
        stringstream str(memory[b+c]);
        int v ;
        str>>v;
        registers[a] = v;
    }

    else if(one == "SW")
    {
        totaltime += time["SW"];
        totalins++;
        // cin>>instruction_3[0]>>instruction_3[1]>>instruction_3[2]
        string instruction_3[3];
        instruction_3[0] = "SW";
        sep>>instruction_3[1];
        sep>>instruction_3[2];
        int a = register_address(instruction_3[1]);

        int memory_len = instruction_3[2].size();
        int h = 0;
        for (int k = 0 ; k < memory_len ; k++){
            if(instruction_3[2][k] != '(')
            {
                h++;
            }
            break;
        }
        string addr = "";
        // char addr[h];
        for (int g = 0 ; g < h ; g++){
        addr+= instruction_3[2][g];
        }
        string reg = "";
        // char reg[memory_len - h - 2];
        for (int g = 0 ; g< (memory_len - h - 2); g++)
        {
        reg += instruction_3[2][g+h+1];
        }
        stringstream b1(addr);
        int b;
        b1>>b;
        int k = register_address(reg);
        int c = registers[k];
         
        stringstream str1;
        str1 << registers[a];
        string s = str1.str();

        memory[b+c] = s ;

    }

    else if(one == "SLL")
    {
        totaltime += time["SLL"];
        totalins++;
        string instruction_4[4];
        // cin>>instruction_4[0]>>instruction_4[1]>>instruction_4[2]>>instruction_4[3] ;
        instruction_4[0] = "SLL";
        sep>>instruction_4[1];
        sep>>instruction_4[2];
        sep>>instruction_4[3];
        int a = register_address(instruction_4[1]);
        int b = register_address(instruction_4[2]);
        // int c = boost::lexical_cast(instruction_4[3]);
        stringstream b1(instruction_4[3]);
        int c;
        b1>>c;
        int value = registers[b];
        for (int k = 0 ; k < c ; k++ ){
        value = value * 2;
    }

    registers[a] = value;
    }

    else if (one == "SRL")
    {
        totaltime += time["SRL"];
        totalins++;
        //cin>>instruction_4[0]>>instruction_4[1]>>instruction_4[2]>>instruction_4[3] ;

        string instruction_4[4];
        instruction_4[0] = "SRL";
        sep>>instruction_4[1];
        sep>>instruction_4[2];
        sep>>instruction_4[3];
        int a = register_address(instruction_4[1]);
        int b = register_address(instruction_4[2]);
        // int c = boost::lexical_cast(instruction_4[3]);
        stringstream b1(instruction_4[3]);
        int c;
        b1>>c;
        int two = 1;
        for (int h = 0 ; h < c ; h++) {
        two = two * 2;
        }
        int value = (int)(registers[b]/two);
        registers[a] = value;
    }

    else if ( one == "BNE")
    {
        totaltime += time["BNE"];
        totalins++;
        // cin>>instruction_4[0]>>instruction_4[1]>>instruction_4[2]>>instruction_4[3] ;
        string instruction_4[4];
        instruction_4[0] = "BNE";
        sep>>instruction_4[1];
        sep>>instruction_4[2];
        sep>>instruction_4[3];
        int a = register_address(instruction_4[1]);
        int b = register_address(instruction_4[2]);

        if (registers[a] != registers[b])
        {
        program_counter = labels[instruction_4[3]];
        program_counter--;
    //mere according yha program_counter jo ki label me store kiya hai wahi hona chahiye
    //kyonki labels me jab jab label ka instruction number store kiya tha tab humne
    //instruction number ko increase nhi kiya tha !
    //aur instruction number wahi tha jo memory array me usko store krne wali block ka number ho
    //ye upar batayi gyi baate sahi hai par humne end me program counter ko +1 kiya hai to wha apne aap
//  ye value aa hi jaaegi jo humko chahiye
        }
    }

    else if (one == "BEQ")
    {
        totaltime += time["BEQ"];
        totalins++;
        // cin>>instruction_4[0]>>instruction_4[1]>>instruction_4[2]>>instruction_4[3] ;
        // in>>instruction_4[0]>>instruction_4[1]>>instruction_4[2]>>instruction_4[3] ;
        string instruction_4[4];
        instruction_4[0] = "BEQ";
        sep>>instruction_4[1];
        sep>>instruction_4[2];
        sep>>instruction_4[3];
        int a = register_address(instruction_4[1]);
        int b = register_address(instruction_4[2]);

        if (registers[a] == registers[b])
        {
        program_counter = labels[instruction_4[3]];
        program_counter--;;
        }
    }

    else if (one == "BLEZ")
    {
        totaltime += time["BLEZ"];
        totalins++;
        // cin>>instruction_3[0]>>instruction_3[1]>>instruction_3[2] ;
        string instruction_3[3];
        instruction_3[0] = "BLEZ";
        sep>>instruction_3[1];
        sep>>instruction_3[2];
        int a = register_address(instruction_3[1]);

        if (registers[a] <= 0)
        {
        program_counter = labels[instruction_3[2]];
        program_counter--;
        }
    }

    else if (one == "BGTZ")
    {
        totaltime += time["BGTZ"];
        totalins++;
        // cin>>instruction_3[0]>>instruction_3[1]>>instruction_3[2] ;
        string instruction_3[3];
        instruction_3[0] = "BGTZ";
        sep>>instruction_3[1];
        sep>>instruction_3[2];
        int a = register_address(instruction_3[1]);

        if (registers[a] > 0)
        {
        program_counter = labels[instruction_3[2]];
        program_counter--;
        }
    }

//jump akela use hota hai par jump and link ke baad humesh jis bhi label pe jump kar rha hai us label
//ke end me jump register lagana padega jisme jis line se humne jump kiya tha uske next wala address
//store kiya hoga humne

    else if (one == "J")
    {
        totaltime += time["J"];
        totalins++;
        // cin>>instruction_2[0]>>instruction_2[1]
        string instruction_2[2];
        instruction_2[0] = "J";
        sep>>instruction_2[1];
        program_counter = labels[instruction_2[1]];
        program_counter--;
    }

    else if (one == "JR")
    {
        totaltime += time["JR"];
        totalins++;
        // cin>>instruction_2[0]>>instruction_2[1] ;
        string instruction_2[2];
        instruction_2[0] = "JR";
        sep>>instruction_2[1];
        int a = register_address(instruction_2[1]);
      //  program_counter = a;
      //yha a se to vo register ka index aaya hai ab us index wale register ke andar ki value nikalni
      //hain,  to most probably program counter uss register ke andar wali value hogi !!
      program_counter  =  registers[a];
        program_counter--;
    }

    else if (one == "JAL")
    {
        totaltime += time["JAL"];
        totalins++;
        // cin>>instruction_2[0]>>instruction_2[1]
        string instruction_2[2];
        instruction_2[0] = "JAL";
        sep>>instruction_2[1];
        registers[31] = program_counter+1;
        program_counter = labels[instruction_2[1]];
        program_counter--;
    }

 program_counter++;
}

int clock_cycle_count = totaltime ;
double avg_instruction_per_cycle = (totalins+0.0)/totaltime;
//your code goes here
cout << "Total number of clock cycle counts: " << clock_cycle_count << "\n";
cout << "Average instructions per cycle (IPC): "  << avg_instruction_per_cycle << "\n";

return 0;
}
