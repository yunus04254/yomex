import websocket
import json
import pandas as pd
from tabulate import tabulate
import os
import time
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

last_time = None
delay_log = []
recent_delays = []

plt.style.use("dark_background")
fig, ax = plt.subplots()
x_data, y_data = [], []

ax.set_title("CB WebSocket Delay")
ax.set_xlabel("Order Index")
ax.set_ylabel("Delay (seconds)")
(line,) = ax.plot(x_data, y_data, "r-", linewidth=2)


def clear_console():
    os.system("cls" if os.name == "nt" else "clear")


def on_message(ws, message):
    global last_time, delay_log, recent_delays
    data = json.loads(message)
    current_time = time.time()

    if data["type"] == "ticker":
        bid = float(data["best_bid"])
        ask = float(data["best_ask"])
        bid_size = float(data["best_bid_size"])
        ask_size = float(data["best_ask_size"])
        price = float(data["price"])
        side = data["side"]
        time_str = data["time"]

        order_book = {
            "Bid Price": [bid],
            "Bid Size": [bid_size],
            "Ask Price": [ask],
            "Ask Size": [ask_size],
            "Last Trade Price": [price],
            "Side": [side],
            "Time": [time_str],
        }

        df = pd.DataFrame(order_book)

        delay = None if last_time is None else current_time - last_time
        if delay is not None:
            delay_log.append(delay)
            recent_delays.append(delay)
            if len(recent_delays) > 3:
                recent_delays.pop(0)
        last_time = current_time

        clear_console()
        print(tabulate(df, headers="keys", tablefmt="grid", showindex=False))

        if recent_delays:
            print("\nMost Recent Delays:")
            for i, d in enumerate(recent_delays[::-1], 1):
                print(f"{i}: {d:.4f} seconds")

        if delay is not None:
            x_data.append(len(delay_log))
            y_data.append(delay)


def on_error(ws, error):
    print(f"Error: {error}")


def on_close(ws, close_status_code, close_msg):
    print("### closed ###")


def on_open(ws):
    subscribe_message = {
        "type": "subscribe",
        "channels": [{"name": "ticker", "product_ids": ["BTC-USD"]}],
    }
    ws.send(json.dumps(subscribe_message))


def update(frame):
    line.set_data(x_data, y_data)
    ax.relim()
    ax.autoscale_view()
    return (line,)


if __name__ == "__main__":
    websocket.enableTrace(False)
    ws = websocket.WebSocketApp(
        "wss://ws-feed.exchange.coinbase.com",
        on_open=on_open,
        on_message=on_message,
        on_error=on_error,
        on_close=on_close,
    )

    ani = FuncAnimation(fig, update, blit=True, interval=100)

    import threading

    ws_thread = threading.Thread(target=ws.run_forever)
    ws_thread.daemon = True
    ws_thread.start()

    plt.show()
