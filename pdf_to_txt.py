# Modules
from os import system
from sys import argv

try: # Try Import module tqdm
    from tqdm import tqdm 
except ModuleNotFoundError: # If "tqdm" was not installed
    system("pip install tqdm")
    from tqdm import tqdm

try: # Try Import module PyPDF2
    from PyPDF2 import PdfFileReader
except ModuleNotFoundError: # If "PyPDF2" was not installed
    system("pip install PyPDF2")
    from PyPDF2 import PdfFileReader

# Colors
Red = "\033[;31;m"
White = "\033[;37;m"
Green = "\033[;32;m"
Line_below_text = "\033[;4;m"
Line_not_below_text = "\033[;0;m"

# Import File PDF
try:
    if argv[1][-4:] == ".pdf":
        Local_file = argv[1]
except IndexError:
    exit(f"""
    
{White}Use: {Green}{Line_below_text}python3 pdf_to_txt.py 'Your file pdf' {Line_not_below_text}

    """)

# Extract the file name for file.txt
if "/" in argv[1]:
    for i in range(1,len(argv[1])):
        if argv[1][-i] == "/":
            save_as = argv[1][-i+1:-4]+".txt"
            break
else:
    save_as = argv[1][:-4]+".txt"

# Convert coordination to file.txt
try:
    pdf_file = PdfFileReader(Local_file)
    num_all_pages = pdf_file.getNumPages()
except (NameError,FileNotFoundError): 
    exit(f"""
{Red}Error!: {Line_below_text}Invalid coordination{Line_not_below_text}

{White}Use: {Green}{Line_below_text}python3 pdf_to_txt.py 'Your file pdf' {Line_not_below_text}

    """)
    
try:
    file_txt = open(save_as,"w")
    for num_page in tqdm(range(num_all_pages)):
        file_txt.writelines(str(pdf_file.getPage(num_page).extractText()))
except KeyboardInterrupt:
    system(f"rm {save_as}")
    print(f"""

{Red}Error!: {Line_below_text}Ctrl + C{Line_not_below_text}
Cancel the process user

""")
