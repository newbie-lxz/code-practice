import requests
r = requests.get('https://www.whu.edu.cn')
print(r.status_code)                             #返回200正常，404失败
print(r.encoding)
print(r.text)