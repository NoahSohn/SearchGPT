import openai
import os

from dotenv import load_dotenv

import wikipedia

import nltk
nltk.download('punkt')

import sumy

from sumy.parsers.plaintext import PlaintextParser
from sumy.nlp.tokenizers import Tokenizer
from sumy.summarizers.lex_rank import LexRankSummarizer

# Load environment variables from .env file
load_dotenv()

# Set up the OpenAI API client
openai.api_key = os.environ.get("OPENAI_API_KEY")

#Ask for user query
query = input("Enter your query: ")

# Set up the model and prompt
model_engine = "text-davinci-003"
prompt = "Turn this into a query most likely to be a Wikipedia article: {}".format(query)

# Generate a response
Completion = openai.Completion.create(
    engine=model_engine,
    prompt=prompt,
    max_tokens=1024,
    n=1,
    stop=None,
    temperature=0.5,
)

response = Completion.choices[0].text

# Step 2: find a wikipedia article most relevant to the query
try:
    page = wikipedia.page(response)
except wikipedia.exceptions.DisambiguationError as e:
    # handle disambiguation error by printing options
    print("Multiple results found. Please refine your query or choose one of the options below:")
    options = e.options
    for i, option in enumerate(options):
        print(f"{i+1}. {option}")
    choice = int(input("Enter the number of your choice: "))
    page = wikipedia.page(options[choice-1])
except wikipedia.exceptions.PageError:
    print("No results found. Please try a different query.")
    quit()

# Step 3: download the text of the wikipedia article
content = page.content

parser = PlaintextParser.from_string(content, Tokenizer('english'))

# Create a LexRank summarizer
summarizer = LexRankSummarizer()

# Summarize the text
summary = summarizer(parser.document, sentences_count=1)

# Print the summary
print(summary[0])

