# ultrasonic-mapper

## Python
### Dependencies
Install the pyserial package using pip3 to manage serial connections
<br />
```pip install pyserial```
### Running the app
Simply use the following command to run the python script
<br />
```python3 main.py```
<br />
<br />
Your output results will be saved in data.csv

## Arduino
- Open ultrasonic_mapper.ino within the folder ultrasonic_mapper in Arduino IDE
- Cofigure your sernsor and servo details in ultrasonic_mapper.ino
- Upload your code to your board and port of choice

## Post-processing
- Go to excel or Google spreadsheets
- Import data.csv into a sheet
- Apply conditional formatting to set colour of each cell to the value it contains
- Make sure to exclude the headers
Example sheet: https://docs.google.com/spreadsheets/d/1a6yX7BsQAT_Z5N_mytXMgCuzLRr44lpg-5WriLbSf8k/