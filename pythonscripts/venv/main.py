import tkinter as tk
from tkinter import ttk
import request as r
import search as s
bgc = "#1e2024"
fgc = "#d5e9f2"
root = tk.Tk()

root.title("SearchGPT")
root.configure(bg=bgc)

aisummary = ""
font = "Calibri"
sources = ["wikipedia", "reddit", "youtube", "qoura"]

s.init_datasets()
airesults = ["","",""]
searchresults = {}
searchquery = ""
maxvalue = 0
maxkey = ""

def askai():
    global aisummary,maxkey,maxvalue,searchquery,searchresults,sources
    proooopmt = textentry.get()
    if proooopmt == "":
        return 0
    airesults[1] = r.askopenai(proooopmt)
    print(aisummary)
    searchquery = r.askopenai("Turn this into a query intended for a search engine:"+str(proooopmt))
    print(searchquery)
    searchresults = s.search(searchquery)
    print(searchresults)

    maxvalue = max(searchresults.values())
    maxkey = max(searchresults, key=searchresults.get)
    print("searched webpage")
    print(maxkey) 
    print(maxvalue)

    sources = searchresults.keys()
    sources = str(sources).replace("dict_keys([", "")
    sources = sources.replace("'", "")
    print(sources)

    with open("datasets/"+maxkey+".crawltxt","r") as f:
        file = f.read()

    file = file.split("<links>", 1)[0]
    print(file)

    aisummary = r.askopenai("answer this proompt with the following conetext: "+proooopmt+file)

    aioutput.configure(state=tk.NORMAL)
    aioutput.delete("1.0", "end")
    aioutput.insert(tk.END, "Ai Summary: " + aisummary)
    aioutput.configure(state=tk.DISABLED)

    sourcesoutput.configure(state=tk.NORMAL)
    sourcesoutput.delete("1.0", "end")
    sourcesoutput.insert(tk.END, "Sources " + str(sources))
    sourcesoutput.configure(state=tk.DISABLED)

    evaluationlabel.configure(text="Evaluated "+str(len(sources))+" Sources")
    #for key in results:
       # results[key]


    #f = open("datasets/" + imaginaryKey + ".crawltxt")



titleframe = tk.Frame(root, bg=bgc, bd=2, relief="groove", height=60)
title = tk.Label(titleframe, text="SearchGPT", bg=bgc, fg=fgc, font=(font, 24))
logoimage = tk.PhotoImage(file="logotk.png", )
logoimage = logoimage.subsample(20)
logo = tk.Label(titleframe, image=logoimage, width=50, height=50, bg=bgc)

titleframe.pack(fill="both", padx=5, pady=10)
title.place(relx=0.40, y=10)
logo.place(anchor="nw")

entryframe = tk.Frame(root, bg=bgc, bd=2, relief="groove", height=60)
textboxlabel = tk.Label(entryframe, text="Enter Search Query", bg=bgc, fg=fgc, font=(font, 12))
evaluationlabel = tk.Label(entryframe, text="Evaluated "+str(len(sources))+" Sources", bg=bgc, fg=fgc, font=(font, 8))
textentry = tk.Entry(entryframe, bg="#a6b4ba")
entrybutton = tk.Button(entryframe, text="Search", command=askai)

entryframe.pack(fill="both", padx=5, pady=10)
textboxlabel.place(x=30, rely=0.2)
evaluationlabel.place(x=200, rely=0.5)
textentry.place(x=175, rely=0.2, relwidth=0.6)
entrybutton.place(relx=0.9, rely=0.2,)


outputframe = tk.Frame(root, bg=bgc, bd=2, relief="groove", height=100)
aioutput = tk.Text(outputframe, bg=bgc, fg=fgc, font=(font, 12), height=5)
outputframe.pack(fill="both", padx=5, pady=10)

aioutput.pack(fill=tk.BOTH, expand=True, padx=10, pady=10,)
aioutput.configure(state=tk.NORMAL)
aioutput.insert(tk.END, "Ai Summary: "+aisummary)
aioutput.configure(state=tk.DISABLED)

sourceoverviewframe = tk.Frame(root, bg=bgc, bd=2, relief="groove",)
sourceoverviewframe.pack(fill="both", padx=5, pady=10)
sourceall = tk.Label(sourceoverviewframe, text="sources", bg=bgc, fg=fgc, font=(font, 12))
sourcesoutput = tk.Text(sourceoverviewframe, bg=bgc, fg=fgc, font=(font, 12), height=5)

sourcesoutput.pack(fill=tk.BOTH, expand=True, padx=10, pady=10,)
sourcesoutput.configure(state=tk.NORMAL)
sourcesoutput.insert(tk.END, "Sources: "+str(sources))
sourcesoutput.configure(state=tk.DISABLED)


root.mainloop()