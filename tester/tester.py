from openpyxl import load_workbook, Workbook
from openpyxl.drawing.image import Image
import pyautogui

# Load the existing Excel file
workbook_path = 'C:/Users/bhave/OneDrive/Documents/bookcancer.xlsx'
workbook = load_workbook(workbook_path)

# Access a specific sheet
sheet = workbook['Sheet1']

# Modify a cell value
# for i in range(1, 5):
#     sheet[f'A{i}'] = "Test"



# Add an image to the worksheet and anchor it to cell B6
img = Image('F:/projects/compsci/tester/sc1.png')
img.width = 200  # set the width (adjust as needed)
img.height = 200  # set the height (adjust as needed)
sheet.add_image(img, 'B6')

# Save the changes
workbook.save('C:/Users/bhave/OneDrive/Documents/test.xlsx')

