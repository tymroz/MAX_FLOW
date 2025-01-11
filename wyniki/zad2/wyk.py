import os
import matplotlib.pyplot as plt

def parse_file(filename):
    """Parsuje dane z pliku wynikowego."""
    with open(filename, 'r') as file:
        lines = file.readlines()
        k = int(lines[0])
        i = int(lines[1])
        max_matching = int(lines[2])
        time = int(lines[3])
    return k, i, max_matching, time

def load_results():
    """Ładuje dane z plików w katalogu."""
    results = []
    for filename in os.listdir():
        if filename.startswith("k") and filename.endswith(".txt"):
            results.append(parse_file(filename))
    return results

def generate_plots(results):
    """Generuje wykresy na podstawie wyników."""
    # Dane dla wykresów
    data_by_k = {}
    data_by_i = {}

    for k, i, max_matching, time in results:
        # Grupowanie danych według k
        if k not in data_by_k:
            data_by_k[k] = {"i": [], "max_matching": []}
        data_by_k[k]["i"].append(i)
        data_by_k[k]["max_matching"].append(max_matching)

        # Grupowanie danych według i
        if i not in data_by_i:
            data_by_i[i] = {"k": [], "time": []}
        data_by_i[i]["k"].append(k)
        data_by_i[i]["time"].append(time)

    for k, data in data_by_k.items():
        sorted_indices = sorted(range(len(data["i"])), key=lambda idx: data["i"][idx])
        data["i"] = [data["i"][idx] for idx in sorted_indices]
        data["max_matching"] = [data["max_matching"][idx] for idx in sorted_indices]

    # Sortowanie danych w grupach według i
    for i, data in data_by_i.items():
        sorted_indices = sorted(range(len(data["k"])), key=lambda idx: data["k"][idx])
        data["k"] = [data["k"][idx] for idx in sorted_indices]
        data["time"] = [data["time"][idx] for idx in sorted_indices]
    # Wykres 1: Maksymalne skojarzenie w zależności od i dla każdego k
    for k, data in data_by_k.items():
        plt.figure()
        plt.plot(data["i"], data["max_matching"], marker="o", label=f"k={k}")
        plt.title(f"Maksymalne skojarzenie w zależności od i (k={k})")
        plt.xlabel("i")
        plt.ylabel("Maksymalne skojarzenie")
        plt.legend()
        plt.grid()
        plt.savefig(f"max_matching_k{k}.png")
        plt.close()

    # Wykres 2: Czas działania w zależności od k dla każdego i
    for i, data in data_by_i.items():
        plt.figure()
        plt.plot(data["k"], data["time"], marker="o", label=f"i={i}")
        plt.title(f"Czas działania w zależności od k (i={i})")
        plt.xlabel("k")
        plt.ylabel("Czas działania [μs]")
        plt.legend()
        plt.grid()
        plt.savefig(f"time_i{i}.png")
        plt.close()

if __name__ == "__main__":
    results = load_results()
    generate_plots(results)
