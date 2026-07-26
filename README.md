# 🛣️ Sistema de Gestão de Portagens com Custo para o Utilizador (CCUT)

> **Unidade Curricular:** Estruturas de Dados  
> **Ano Letivo:** 2024/2025  

---

## 📌 Descrição do Projeto

Este projeto consiste no desenvolvimento de um sistema de informação para a gestão e análise de veículos e passagens numa rede de auto-estradas equipada com sensores de monitorização.

A aplicação processa ficheiros de entrada com dados de utilizadores, veículos, sensores, distâncias e passagens registadas. Através do uso eficiente de **Estruturas de Dados** (Listas Ligadas, Tabelas de Hash e/ou Árvores) e algoritmos de ordenação e pesquisa, o sistema permite a consulta de estatísticas de utilização, deteção de infrações de velocidade e exportação de dados.

---

## 📁 Estrutura dos Ficheiros de Entrada

O sistema efetua a leitura inicial de dados através dos seguintes ficheiros de texto:

* `Donos.txt` — Registo dos condutores/utilizadores (`NumContribuinte`, `Nome`, `CodPostal`).
* `Carros.txt` — Registo dos veículos (`Matricula`, `Marca`, `Modelo`, `Ano`, `Dono`, `CodVeiculo`).
* `Sensores.txt` — Localização e identificação dos sensores (`CodSensor`, `Designacao`, `Latitude`, `Longitude`).
* `Distancias.txt` — Distâncias quilométricas entre sensores (`CodSensor1`, `CodSensor2`, `Distancia`).
* `Passagem.txt` — Registo de entradas e saídas nos sensores (`IdSensor`, `CodVeiculo`, `Data/Hora`, `TipoRegisto`: 0=Entrada, 1=Saída).

---

## ⚙️ Funcionalidades Requeridas

### 📋 Operações Base e Gestão
* **Importação de Ficheiros:** Leitura e carregamento de dados para memória.
* **Menu de Consola:**
  * Registar e Listar Donos.
  * Registar e Listar Veículos.
  * Registar Passagens de Veículos.
* **Memória:** Cálculo da memória consumida por todas as estruturas de dados.
* **Exportação:** Exportação integral da Base de Dados para formatos `.csv` e `.xml`.

### 📊 Consultas, Estatísticas e Rankings
* **Listagens Ordenadas:**
  * Condutores ordenados alfabeticamente.
  * Condutores ordenados por número de contribuinte.
  * Veículos ordenados por Matrícula, Marca ou Modelo.
  * Veículos que circularam num determinado período $X$.
* **Rankings de Circulação:**
  * Ranking de quilómetros percorridos por veículo num período $X$.
  * Ranking de quilómetros percorridos por marca num período $X$.
* **Deteção de Infrações e Velocidades:**
  * Listagem de veículos com velocidade média **> 120 km/h** num determinado período.
  * Ranking de infrações acumuladas por veículo.
  * Determinação da marca e do condutor com maior velocidade média.
  * Velocidade média por código postal.
* **Análise Geral:**
  * Identificação da marca de automóvel mais comum.

---

## 🛠️ Linguagens e Ferramentas Utilizadas

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![VS Code](https://img.shields.io/badge/VS%20Code-007ACC?style=for-the-badge&logo=visual-studio-code&logoColor=white)
![Visual Studio 2022](https://img.shields.io/badge/Visual%20Studio%202022-5C2D91?style=for-the-badge&logo=visual-studio&logoColor=white)
![Doxygen](https://img.shields.io/badge/Doxygen-008080?style=for-the-badge&logo=doxygen&logoColor=white)
