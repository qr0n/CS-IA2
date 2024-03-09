from openpyxl import load_workbook, Workbook
from openpyxl.drawing.image import Image
import pyautogui
import pygetwindow as gw
import time

workbook_path = 'C:/Users/bhave/OneDrive/Documents/test.xlsx'
workbook = load_workbook(workbook_path)

sheet = workbook['Sheet1']
left, top, width, height = 100, 100, 500, 500

class ExcelFileManagement:
    @staticmethod
    def add_value(cell_id, text):
        try:
            sheet[cell_id] = text
            workbook.save(workbook_path)
            return "Done"
        except Exception as E:
                return E
        
    @staticmethod
    def add_image_to_cell(cell_id, image_path, width, height):
        try:
            img = Image(image_path)
            img.width = width
            img.height = height
            sheet.add_image(img, cell_id)
            workbook.save(workbook_path)
            return "Done"
        except Exception as E:
            return E
            
    @staticmethod
    def populate_table(lines, module=None, expected=None, actual=None):
        headers = ["Test number", "Test Type", "Variables", "Module", "Input", "Expected result", "Actual result", "Screenshot"]
        for i, header in enumerate(headers, start=1):
            sheet.cell(row=i, column=1, value=header)

        ScreenshotManagement.take_screenshot("F:/projects/compsci/tester/test.png")
        # input lines
        test_type = input("What type of test is this?\n> ")
        variable_input = input("Paste the variables your function is using here\n> ")
        input_input = input(f"What is the input for this {test_type} test?\n> ")
        # Add lines to the sheet
        for i in range(1, lines + 1):
                # Your logic for generating test data goes here
                            test_data = [int(i),
                            str(test_type), 
                            str(variable_input),
                            str(module),
                            str(input_input),
                            str(expected),
                            str(actual),
                            ExcelFileManagement.add_image_to_cell("B8", "F:/projects/compsci/tester/test.png", width=100, height=100)
                            ]

                # Append the test data to the sheet in column B (2nd column)
                            for j, data in enumerate(test_data, start=0):  # Start from row 1
                                  sheet.cell(row=j + 1, column=2, value=data)

                            # Save the workbook
                            workbook.save(workbook_path)

class ScreenshotManagement:
    # class Helper:
    #     def focus_window_by_title(window_title):
    #         try:
    #             window = gw.getWindowsWithTitle(window_title)[0]
    #             window.activate()
    #             return True
    #         except IndexError:
    #             print(f"Window with title '{window_title}' not found.")
    #             return False
            
    @staticmethod
    def take_screenshot(path_to_save):
        screenshot = pyautogui.screenshot(region=(left, top, width, height))
        screenshot.save(path_to_save)
    
ExcelFileManagement.populate_table(1, 8, "main", "Hello world", "...", "...")