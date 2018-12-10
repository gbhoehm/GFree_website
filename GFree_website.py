import os
from flask import Flask, render_template, url_for
app = Flask(__name__)

# Some data to test the review section in the product page
reviews = [
    {
        "reviewer": "gage boehm",
        "title": "sorgum flour post 1",
        "content": "It's greate stuff",
        "dataposted": "november 28, 2018"
    },
    {
        "reviewer": "salem boehm",
        "title": "sorgum flour post 2",
        "content": "It's okay stuff",
        "dataposted": "november 29, 2018"
    },
    {
        "reviewer": "salem boehm",
        "title": "sorgum flour post 2",
        "content": "It's okay stuff",
        "dataposted": "november 29, 2018"
    },
    {
        "reviewer": "salem boehm",
        "title": "sorgum flour post 2",
        "content": "It's okay stuff",
        "dataposted": "november 29, 2018"
    },
    {
        "reviewer": "salem boehm",
        "title": "sorgum flour post 2",
        "content": "It's okay stuff",
        "dataposted": "november 29, 2018"
    },
    {
        "reviewer": "salem boehm",
        "title": "sorgum flour post 2",
        "content": "It's okay stuff",
        "dataposted": "november 29, 2018"
    }
]

# product data for the product page.  
# needs a different approach as in it will need multiple dictionary must likely. 
products = [
    {
        "image":"sorghum grain",
        "description": "placeholder"
    },
    {
        "image":"sorghum flower",
        "description": "placeholder"
    },
    {
        "image":"sorghum seeds",
        "description": "placeholder"
    }
]

# Setting up the domain of the homepage and then calling the html file
@app.route("/")
@app.route("/home")
def home():
    return render_template('home.html')

# Setting up the product page domain and then calling the product page passing in variables for the Jinja code
@app.route("/product")
def about():
    return render_template('product.html', title = "product", reviews = reviews, products = products)


    
# This allows for the website to be reloaded and see the changes with out having to reset the website eac change.
if __name__ == "__main__":
    app.run(debug = True)