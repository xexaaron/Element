#!/usr/bin python
import os
import json
import datetime

if os.path.exists('reverse_change_log.txt'):
    os.remove('reverse_change_log.txt')
    

log_file_path = 'reverse_change_log.txt'
log = open(log_file_path, 'a')  


with open('Super.json') as json_file:
    data = json.load(json_file)


# Iterate through each entry in the JSON data
for file_path, details in data.items():
  
    if os.path.exists(file_path):
      
        with open(file_path, 'r') as file:
            lines = file.readlines()

        replaced_content = ""
        for line_number, line in enumerate(lines, start=1):
            if "::" in line:
                replaced_line = line.replace(details['parent'], 'Super')

                # Check if 'Super' doesn't have any letters preceding it
                if not replaced_line.startswith(('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                                 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                                 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                                 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z')):
                    replaced_content += replaced_line
                else:
                    replaced_content += line
            else:
                replaced_content += line

      
        with open(file_path, 'w') as file:
            file.write(replaced_content)

        Instances = replaced_content.count(f"{details['parent']}")
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        log_entry = f"{timestamp}: Replaced '{details['parent']}' with 'Super' in {file_path}\n"
        log.write(log_entry)
        log.write("------------------------------------------------------------------------------------------\n")

log.close()
