import sys
import requests
from bs4 import BeautifulSoup

def get_google_search_links(query, num_results=5):
    # format the Google search URL with the user's query
    search_url = f"https://www.google.com/search?q={query}"
    
    # send a request to the Google search URL and get the HTML response
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36'}
    response = requests.get(search_url, headers=headers)
    html = response.content
    
    # parse the HTML response with BeautifulSoup
    soup = BeautifulSoup(html, 'html.parser')
    
    # find all search result links
    search_results = soup.find_all('div', {'class': 'g'})
    links = []
    for i, result in enumerate(search_results):
        if i >= num_results:
            break
        link = result.find('a')['href']
        links.append(link)
    return links


if __name__ == '__main__':
    # get the user's search query from the command line
    query = ' '.join(sys.argv[1:])
    
    # get the top 5 Google search links for the query
    links = get_google_search_links(query, num_results=5)
    
    if links:
        # print the links
        for i, link in enumerate(links):
            print(f"{i+1}. {link}")
    else:
        print(f"No search results found for '{query}'")
