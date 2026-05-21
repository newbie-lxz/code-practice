import requests
import re
from bs4 import BeautifulSoup
r = requests.get('https://www.whu.edu.cn')
r.encoding = r.apparent_encoding
demo = r.text
print(r.encoding)
soup = BeautifulSoup(demo,'html.parser')
a_all = soup.find_all('a',string = re.compile('武汉大学'))  #string = re.compile('武汉大学') 正则表达式，在a标签中匹配“武汉大学”4个字 .find_all返回所有标签
for tag in a_all:
        print(tag.string)
print(soup.title.string)