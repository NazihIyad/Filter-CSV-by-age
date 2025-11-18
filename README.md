
Add people: 
@"
Alice,12
Bob,20
Charlie,15
David,17
Eve,10
Frank,22
Grace,14
"@ | Set-Content input.csv

creating an error: 
@"
Alice,12
Bob,
Charlie,abc
,15
David,17
"@ | Set-Content input.csv

then run: 
.\main.exe 17 input.csv



<img width="214" height="243" alt="image" src="https://github.com/user-attachments/assets/b1f8349d-75e6-494a-b0ac-9b0026cc5b0f" />
