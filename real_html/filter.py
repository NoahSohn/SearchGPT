from bs4 import BeautifulSoup

# Read in the HTML file
with open('coral.html') as file:
    html = file.read()

# Parse the HTML with BeautifulSoup
soup = BeautifulSoup(html, 'html.parser')

# Extract the text from the soup object
text = soup.get_text()

# Print the text
with open('filtered_text.txt', 'w') as file:
    file.write(text)