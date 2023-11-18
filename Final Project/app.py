import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
from helpers import apology, login_required, lookup, usd
import bisect

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    transactions_db = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    funds_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    funds = funds_db[0]["cash"]

    return render_template("index.html", database=transactions_db, cash=funds)


@app.route("/calcul_electromagnet", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("calcul_electromagnet.html")
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if shares.isdigit():
            shares = int(float(shares))
        else:
            shares = 0
        date = datetime.datetime.now()
        user_id = session["user_id"]

        if not symbol:
            return apology("Trebuie introdusa valoarea fortei", 400)
        if not shares:
            return apology("Trebuie introdusa valoarea intrefierului", 400)
        if shares < 0:
            return apology("Valoarea intrefierului trebuie sa fie pozitiva", 400)
        if symbol < 0:
            return apology("Valoarea fortei trebuie sa fie pozitiva", 400)

        coeficient_magnet = symbol/shares

        ### valori BUNE, DE FACUT CALCULELE PENTRU FIECARE VARIABILA.

        if coeficient_magnet > 84600:
            flash("Succes!")
            return apology("Tipul electromagnetului: Cu armatura fixa in manta", redirect("/armatura_fixa_in_manta"))
        if coeficient_magnet > 29000 and coeficient_magnet <= 84600:
            flash("Succes!")
            return apology("Tipul electromagnetului: Cu armatura fixa in U", redirect("/armatura_fixa_in_u"))
        if coeficient_magnet > 5200 and coeficient_magnet <= 29000:
            flash("Succes!")
            return apology("Tipul electromagnetului: Cu plonjor cu opritor si intrefier plan", redirect("/plonjor_cu_opritor_plan"))
        if coeficient_magnet > 1180 and coeficient_magnet <= 5200:
            flash("Succes!")
            return apology("Tipul electromagnetului: Cu plonjor cu opritor si intrefier conic", redirect("/plonjor_cu_opritor_conic"))
        if coeficient_magnet > 68 and coeficient_magnet <= 1180:
            flash("Succes!")
            return apology("Tipul electromagnetului: Cu plonjor scurt, fara opritor", redirect("/plonjor_scurt"))
        if coeficient_magnet <= 68:
            flash("Succes!")
            return apology("Tipul electromagnetului: Cu plonjor lung, fara opritor", redirect("/plonjor_lung"))


@app.route("/armatura_fixa_in_manta")
@login_required
def armatura_fixa_in_manta():
    forta = lookup(symbol())
    densitatea_fluxului_magnetic = request.form.get("densitatea_fluxului_magnetic")

    ### calcul densitatea fluxului magnetic


    permeabilitatea_relativa_vid = 1.257*10^(-6)
    Aria_plonjor_maxima = (2 * permeabilitatea_relativa_vid * forta) / densitatea_fluxului_magnetic
    diametru_plonjor = round(sqrt((4 *Aria_plonjor_maxima) / 3.14159 ))
    Aria_plonjor = (diametru_plonjor^2 * 3.14159) / 4
    Forta1 = (Aria_plonjor * densitatea_fluxului_magnetic^2) / ( 2 * permeabilitatea_relativa_vid)
    intrefier = lookup(shares())
    solenatia = (densitatea_fluxului_magnetic * intrefier) / (0.7 * permeabilitatea_relativa_vid)

    # de facut lista ca la sell pentru a alege materialele din database

    material_conductor = request.form.get("material_conductor")
    rezistivitatea_db = materiale.execute("SELECT rezistivitatea FROM materiale WHERE material = ?", material_conductor)
    conductivitatea_db = materiale.execute("SELECT conductivitatea FROM materiale WHERE material = ?", material_conductor)
    coeficientul_db = materiale.execute("SELECT coeficientul FROM materiale WHERE material = ?", material_conductor)

    rezistivitatea_temperatura = rezistivitatea_db * (1 + coeficientul_db * (70))

    inaltime_electromagnet = round(((5 * rezistivitatea_temperatura * solenatia^2 * Dc)/(2 * 4 * 0.4 * 40))^(1/3))

    diametru_mosor = round(inaltime_electromagnet/2 - diametru_plonjor)

    kf = 0.8

    diametru_bobinaj = round(sqrt(((diametru_plonjor)^2)/kf + diametru_mosor^2))
    grosime_bobinaj = diametru_mosor - diametru_plonjor


    tensiune_lucru = request.form.get("tensiune_lucru")

    diametru_sarma = sqrt((4 * rezistivitatea_temperatura * (diametru_mosor + diametru_plonjor) * solenatia) / tensiune_lucru)

    ## lucru cu baze de date sarma cupru

    diametre_db = materiale.execute("SELECT diametru FROM sarma")
    lista_diametre = []

    for x in diametre_db:
        lista_diametre.append(int(x))


    bisect.insort(lista_diametre, diametru_sarma)

    for x in lista_diametre:
        if x == diametru_sarma:
            varianta_diametru_1 = lista_diametre[lista_diametre.index(x) - 2]
            varianta_diametru_2 = lista_diametre[lista_diametre.index(x) - 1]
            varianta_diametru_3 = lista_diametre[lista_diametre.index(x) + 1]
            varianta_diametru_4 = lista_diametre[lista_diametre.index(x) + 2]

    ## lista alegere diametre // posibil sa transmit spre alta pagina
    




@app.route("/armatura_fixa_in_u")
@login_required
def armatura_fixa_in_u():
    forta = lookup(symbol())
    densitatea_fluxului_magnetic = request.form.get("densitatea_fluxului_magnetic")
    permeabilitatea_relativa_vid = 1.257*10^(-6)


@app.route("/plonjor_cu_opritor_plan")
@login_required
def plonjor_cu_opritor_plan():
    forta = lookup(symbol())
    densitatea_fluxului_magnetic = request.form.get("densitatea_fluxului_magnetic")
    permeabilitatea_relativa_vid = 1.257*10^(-6)


@app.route("/plonjor_cu_opritor_conic")
@login_required
def plonjor_cu_opritor_conic():
    forta = lookup(symbol())
    densitatea_fluxului_magnetic = request.form.get("densitatea_fluxului_magnetic")
    permeabilitatea_relativa_vid = 1.257*10^(-6)


@app.route("/plonjor_scurt")
@login_required
def plonjor_scurt():
    forta = lookup(symbol())
    densitatea_fluxului_magnetic = request.form.get("densitatea_fluxului_magnetic")
    permeabilitatea_relativa_vid = 1.257*10^(-6)


@app.route("/plonjor_lung")
@login_required
def plonjor_lung():
    forta = lookup(symbol())
    densitatea_fluxului_magnetic = request.form.get("densitatea_fluxului_magnetic")
    permeabilitatea_relativa_vid = 1.257*10^(-6)


@app.route("/login", methods=["GET", "POST"])
def login():

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()
    username = request.form.get("username")
    password = request.form.get("password")
    confirm = request.form.get("confirmation")
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "GET":
        return render_template("register.html")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Ensure username was submitted

        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)
        elif not confirm:
            return apology("must provide confirmation", 400)
        elif confirm != password:
            return apology("confirm must match password", 400)

        hash = generate_password_hash(password)

        try:
            registered_user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except:
            return apology("Username Already Exists", 400)
        session["user_id"] = registered_user

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)

