import os
from uuid import uuid4
from flask import Flask, render_template, url_for, request, send_from_directory
app = Flask(__name__)
APP_ROOT =  os.path.dirname(os.path.abspath(__file__))

# Some data to test the review section in the product page
reviews_flour = [
    {
        "title": "sorghum flour post 1",
        "content": "It's great stuff",
    },
    {
        "title": "sorghum flour post 2",
        "content": "It's okay stuff",
    },
    {
        "title": "sorghum flour post 2",
        "content": "It's okay stuff",
    },
    {
        "title": "sorghum flour post 2",
        "content": "It's okay stuff",
    },
    {
        "title": "sorghum flour post 2",
        "content": "It's okay stuff",
    },
    {
        "title": "sorghum flour post 2",
        "content": "It's okay stuff",
    }
]
reviews_grain = [
    {
        "title": "sorghum grain post 1",
        "content": "It's great stuff",
    },
    {
        "title": "sorghum grain post 2",
        "content": "It's okay stuff",
    },
    {
        "title": "sorghum grain post 2",
        "content": "It's okay stuff",
    },
    {
        "title": "sorghum grain post 2",
        "content": "It's okay stuff",
    },
    {
        "title": "sorghum grain post 2",
        "content": "It's okay stuff",
    },
    {
        "title": "sorghum grain post 2",
        "content": "It's okay stuff",
    }
]


spacing = [" "," "," "," "," ",""]

@app.route("/upload", methods=["POST"])
def upload():
    folder_name = request.form['superhero']
    target = os.path.join(APP_ROOT, 'files/{}'.format(folder_name))
    print(target)
    if not os.path.isdir(target):
        os.mkdir(target)
    print(request.files.getlist("file"))
    for upload in request.files.getlist("file"):
        print(upload)
        print("{} is the file name".format(upload.filename))
        filename = upload.filename
        # This is to verify files are supported
        ext = os.path.splitext(filename)[1]
        if (ext == ".jpg") or (ext == ".png"):
            print("File supported moving on...")
        else:
            render_template("Error.html", message="Files uploaded are not supported...")
        destination = "/".join([target, filename])
        print("Accept incoming file:", filename)
        print("Save it to:", destination)
        upload.save(destination)

    # return send_from_directory("images", filename, as_attachment=True)
    return render_template("complete.html", image_name=filename)



# Setting up the domain of the homepage and then calling the html file
@app.route("/")
@app.route("/home")
def home():
    image_names = os.listdir('./images')
    print(image_names)
    return render_template('home.html', image_names = image_names, spacing = spacing)

@app.route('/upload/<filename>')
def send_image(filename):
    return send_from_directory("images", filename)

# Setting up the product page domain and then calling the product page passing in variables for the Jinja code
@app.route("/product_flour")
def about_1():
    image_names = os.listdir('./images')
    print(image_names)
    return render_template('product_flour.html', title = "product", reviews = reviews_flour, image_names = image_names)

# Setting up the product page domain and then calling the product page passing in variables for the Jinja code
@app.route("/product_grain")
def about_2():
    image_names = os.listdir('./images')
    print(image_names)
    return render_template('product_grain.html', title = "product", reviews = reviews_grain, image_names = image_names)

    
# This allows for the website to be reloaded and see the changes with out having to reset the website eac change.
if __name__ == "__main__":
    app.run(debug = True)