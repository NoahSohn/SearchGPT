import tkinter as tk

root = tk.Tk()
root.title("what the FUK am i doing here")
root.minsize(720,480)

text = ["", "WHY WHY WHY WHW"]
visible = 1


def toggle():
    global visible
    if visible == 1:
        label.config(text=text[visible])
        visible = 0
    else:
        label.config(text=text[visible])
        visible = 1


label = tk.Label(root, text=text[visible],)

button = tk.Button(root, text="HELP HELP HELP", command=toggle)

box = tk.Entry(root, text="FUCK FUCK FUCK ")

button.grid(column=1,row=2)
label.grid(column=2, row=1)
box.grid(column=1, row=3)
root.mainloop()