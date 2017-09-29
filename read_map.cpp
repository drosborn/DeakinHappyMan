// basic file operations
#include "splashkit.h"
#include "happy_man.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void read_map(level_data &level)
{
  string file;  
  map_data map;
    vector<map_type> temp_row;
    int row_size = 0;
    int max_size = 0;
    bool rows_same = true;

    switch(level.level_number){
      case 0:   file = "one.level";
                break;
      case 1:   file = "two.level";
                break;
      case 2:   file = "three.level";
                break;
      default:  file = "bonus.level";
                break;
    }
      
    string line;
    ifstream myfile (file);
    
    if (myfile.is_open())
    {
      while ( getline (myfile,line))
      {        
        if(line != "")
        {
          for(char c:line)
          {     
            if (c == 'P')
            {
              temp_row.push_back(PATH);
            }
            else
            {
              temp_row.push_back(WALL);
            }
          }
          level.map.map_array.push_back(temp_row);

          if(row_size == 0 || row_size == temp_row.size())
          {
            write_line("row_size");
            write_line(to_string(row_size));
            write_line("row_size");
          
            write_line(to_string(temp_row.size()));
              if(row_size < temp_row.size())
              {
                write_line("aaa");
                row_size = temp_row.size();
              }
          }
          else
          {
            write_line("dcdcdc");
            rows_same = false;
            if(row_size < temp_row.size())
            {
              write_line("aaa");
              row_size = temp_row.size();
            }
          }
          
          temp_row.clear();
          line = "";
        }
      }
      myfile.close();
    }
  
    else cout << "Unable to open file"; 

    if(rows_same == false)
    {
      write_line("123");
      for(int i = 0; i < level.map.map_array.size() ; i++)
      {
        write_line("456");
        if(level.map.map_array[i].size() != row_size)
        {
          write_line("789");
          while(level.map.map_array[i].size() < row_size)
          {
            level.map.map_array[i].push_back(WALL);
            write_line("abc");
          }
        }
      }
    }

    level.map.x_segements_map = level.map.map_array[0].size();
    level.map.y_segements_map = level.map.map_array.size();
    
    populate_directions(level.map);
}