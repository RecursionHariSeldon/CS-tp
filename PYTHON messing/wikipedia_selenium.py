from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

site = "https://www.wikipedia.org/"

driver = webdriver.Chrome()

driver.get(site)

driver.find_element(By.ID, "searchInput").send_keys("France")

time.sleep(5)

WebDriverWait(driver, 2).until(
    EC.presence_of_element_located((By.CLASS_NAME, "suggestion-title"))
)# to wait for the drop down options to appear properly 
#if it doesn't appear in 10 secs the it gives error

suggestions = driver.find_elements(By.CLASS_NAME, "suggestion-title")

suggestions[1].click()
time.sleep(2)

imgs = driver.find_elements(By.XPATH,"//img")

list = [3,4,5,6,7,8,9]
list_src = []
for i in list:
    p = imgs[i].get_attribute("src")
    list_src.append(p)

for i in list_src:
    driver.get(i)
    time.sleep(2)    