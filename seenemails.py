"""
Script: mark_all_emails_as_read.py
Description:
    This script automates the process of opening Gmail in a browser and marking all emails as read.
    It uses pyautogui to locate and interact with screen elements using screenshots.
    Screenshots required: 'select_all.png' and 'mark_as_read.png'.
Usage:
    Run the script. It will open Gmail in a new browser tab, wait for it to load,
    select all visible emails, and click the "mark as read" icon if available.
    !Note: Works only on gmail.

Author: [Eng/Adel elnimr]
Date: [30/4/2025]
"""

import pyautogui
from time import sleep
import webbrowser as wb

url='https://gmail.com'

wb.open(url, new=2, autoraise=True)

position=None
while position is None: 
    try:
        position=pyautogui.locateOnScreen ('select_all.png')
        sleep(4)
    except pyautogui.ImageNotFoundException:
        print('webpage is still loading, wait...')

pyautogui.click('select_all.png')
sleep(1)

try:
    pyautogui.click('mark_as_read.png')
except pyautogui.ImageNotFoundException:
    print('all emails are seen already')
