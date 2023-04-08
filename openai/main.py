import openai

# Set up the OpenAI API client
openai.api_key = "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"

# Set up the model and prompt
model_engine = "text-davinci-003"
prompt = "Placeholder ChaTGPT request"

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