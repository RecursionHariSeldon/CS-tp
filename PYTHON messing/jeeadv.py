from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
from selenium import webdriver
from selenium.common.exceptions import NoSuchElementException

site = "https://results2.jeeadv.ac.in/"
thisTry = 0
while (True): 
    driver = webdriver.Chrome()

    driver.get(site)

    time.sleep(4)

    roll = "241104239"
    dob = "01/08/2006"
    mob = "9820470030"

    try:
        driver.find_element(By.XPATH,"//input[@placeholder ='9-digit JEE (Advanced) roll number']").send_keys(roll)

    except NoSuchElementException:  #spelling error making this code not work as expected
        driver.quit()
        time.sleep(2)
        continue

    driver.find_element(By.NAME,"dob").send_keys(dob)
    driver.find_element(By.XPATH,"//input[@placeholder ='10 digit mobile number']").send_keys(mob)
    time.sleep(2)
    driver.find_element(By.XPATH,"/html/body/div/div[5]/button").click()

    thisTry += 1
    for i in range(10):
        print("Try - ",thisTry ," - wait - " , i)
        time.sleep(1)
