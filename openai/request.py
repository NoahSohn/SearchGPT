import openai

import os

from dotenv import load_dotenv

# Load environment variables from .env file
load_dotenv()

# Set up the OpenAI API client
openai.api_key = os.environ.get("OPENAI_API_KEY")

#Ask for user query
query = input("Enter your query: ")

# Set up the model and prompt
model_engine = "text-davinci-003"
prompt = "Turn this into a query intended for a search engine: {}".format(query)

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
print(response)