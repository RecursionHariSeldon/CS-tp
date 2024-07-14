from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
from pynput.keyboard import Key, Controller


driver = webdriver.Chrome()
driver.get("https://www.google.com/?olud")
driver.find_element(By.CLASS_NAME,"DV7the").click()
time.sleep(1)

keyboard = Controller()
keyboard.type("file:///C:/Users/rachi/OneDrive/Desktop/CS/PYTHON%20messing/captcha.jpg")
time.sleep(1)
keyboard.press(Key.enter)
keyboard.release(Key.enter)
time.sleep(3)

driver.find_element(By.ID,"ucj-2").click()
time.sleep(3)

driver.find_element(By.CLASS_NAME,"VfPpkd-LgbsSe.VfPpkd-LgbsSe-OWXEXe-k8QpJ.VfPpkd-LgbsSe-OWXEXe-dgl2Hf.nCP5yc.AjY5Oe.DuMIQc.LQeN7.kCfKMb").click()
time.sleep(3)
number = driver.find_element(By.CLASS_NAME,"wCgoWb").text

print(number)
time.sleep(1200)