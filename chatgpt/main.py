import openai

# Set up the OpenAI API client
openai.api_key = "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"

# Set up the model and prompt
model_engine = "text-davinci-003"
prompt = "A hackathon (also known as a hack day, hackfest, datathon or codefest; a portmanteau of hacking and marathon) is an event where people engage in rapid and collaborative engineering over a relatively short period of time such as 24 or 48 hours. They are often run using agile software development practices, such as sprint-like design wherein computer programmers and others involved in software development, including graphic designers, interface designers, product managers, project managers, domain experts, and others collaborate intensively on engineering projects, such as software engineering. Can you please summarize this ?"

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