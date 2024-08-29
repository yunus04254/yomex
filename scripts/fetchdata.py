import requests
import json
import os
from dotenv import load_dotenv

load_dotenv()

AV_API_KEY = os.getenv("AV_API_KEY")
CB_API_KEY = os.getenv("CB_API_KEY")
PAIR = "BTC-USD"  # Currently for CB api


def fetch_order_book():
    url = f"https://api.exchange.coinbase.com/products/{PAIR}/book?level=2"
    headers = {
        "Accept": "application/json",
        "CB-ACCESS-KEY": CB_API_KEY,
    }
    response = requests.get(url, headers=headers)
    data = response.json()
    with open("../data/order_book.json", "w") as f:
        json.dump(data, f, indent=4)


def fetch_daily():
    url = f"https://www.alphavantage.co/query"
    params = {
        "function": "DIGITAL_CURRENCY_DAILY",
        "symbol": "BTC",
        "market": "USD",
        "apikey": AV_API_KEY,
    }
    response = requests.get(url, params=params)
    data = response.json()
    with open("../data/daily.json", "w") as f:
        json.dump(data, f, indent=4)


if __name__ == "__main__":
    fetch_order_book()
    fetch_daily()
