from flask import Flask, request, render_template
import sounddevice as sd
import soundfile as sf


app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/wait_for_keyword')
def wait_for_keyword():
    keyword = request.args.get('keyword')
    # code to wait for keyword goes here
    return "OK"

@app.route('/record/start', methods=['POST'])
def start_recording():
    filename = request.args.get('filename')
    # code to start recording goes here
    duration = 10  # seconds
    fs = 44100
    print(f"Recording audio to {filename}...")
    myrecording = sd.rec(int(duration * fs), samplerate=fs, channels=2)
    sd.wait()
    sf.write(filename, myrecording, fs)
    return "OK"

if __name__ == '__main__':
    app.run(debug=True)
