from flask import Flask, render_template, request, url_for, redirect
import pandas as pd

app = Flask(__name__, template_folder='templates')

@app.route('/')
def index():
    return render_template('index.html')
    
@app.route('/login', methods=['POST'])
def login():
    name = request.form.get('username') # request.form['name']
    password = request.form.get('password')
    if name == 'mahmoud' and password == '1234':
        return 'Logged in successfully'
    return 'Invalid credentials'

@app.route('/file_upload', methods=['POST'])
def file_upload():
    file = request.files['file']
    if file.content_type == 'text/plain':
        return file.read().decode()
    elif file.content_type == 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet':
        df = pd.read_excel(file)
        return df.to_csv()
    return 'Invalid file type'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port = 5000, debug=True)