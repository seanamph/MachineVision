from selenium import webdriver
from selenium.webdriver.edge.service import Service
from webdriver_manager.microsoft import EdgeChromiumDriverManager

# 设置WebDriver
service = Service(EdgeChromiumDriverManager().install())
driver = webdriver.Edge(service=service)

# 打开网页
driver.get("https://www.idx.co.id/primary/home/GetIndexList")

# 获取页面的HTML
html_content = driver.page_source
print(html_content)

# 关闭浏览器
driver.quit()
