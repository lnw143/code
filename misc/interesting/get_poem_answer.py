from selenium import webdriver
from selenium.webdriver.common.by import By
import requests
from bs4 import BeautifulSoup
import re
import pandas.io.clipboard as cb

proxies = {
    "http": "http://127.0.0.1:7890/",
    "https": "http://127.0.0.1:7890/",
}

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3"
}

print('getting problem...')

options = webdriver.ChromeOptions()
options.add_argument('--ignore-certificate-errors')
options.add_experimental_option('excludeSwitches', ['enable-logging'])

browser = webdriver.Chrome(options=options)

browser.get('https://poem.rotriw.com/')

problem = browser.find_element(value="problem_now").text
print('the problem is ' + problem)

browser.quit()

print('getting answer...')

result = requests.get('https://www.gushiwen.cn/search.aspx?value=' +
            problem + '&valuej=' + problem, headers=headers, proxies=proxies)

bs = BeautifulSoup(result.text, "html.parser")

answer = bs.find_all('div', class_='contson')

if len(answer) == 0:
    print('no answer found')
else:
    answers = []
    for i in answer:
        content = i.text
        sentences = re.split('([。！？])', content)
        for j in range(len(sentences)):
            if problem in sentences[j]:
                output = sentences[j] + sentences[j+1]
                output = output.replace('\n', '')\
                    .replace('\r', '').replace(' ', '').replace('\u3000', '')
                if len(output) < 20:
                    answers.append(output)
    print(answers)
    cb.copy(answers[0])
    print('answer copied to clipboard')