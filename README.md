# 🛒 Sistema de Gerenciamento de Produtos

Este projeto é um Sistema de Gerenciamento de Produtos desenvolvido em linguagem C, como parte de uma tarefa universitária da Universidade Veiga de Almeida.  
O sistema permite o cadastro, consulta, alteração e exclusão de produtos, além de gerenciar um carrinho de compras para simular pedidos.

---

## ⚙️ Funcionalidades

### 📦 Gerenciar Produtos
- ➕ Incluir novos produtos  
- ✏️ Alterar dados de produtos existentes  
- 📋 Listar todos os produtos cadastrados  
- 🔍 Consultar detalhes de um produto específico  
- 🗑️ Excluir produtos do sistema  

### 🛒 Registrar Pedido de Compra
- ➕ Adicionar produtos ao carrinho de compras  
- 📄 Consultar o carrinho de compras  
- 🗑️ Excluir produtos do carrinho  
- ✏️ Alterar a quantidade de produtos no carrinho  
- ✅ Finalizar o pedido (atualizando o estoque)  
- 🧹 Esvaziar o carrinho  

### 🧹 Excluir Tudo
- 🗑️ Remove todos os produtos cadastrados e limpa o carrinho  

### 💾 Persistência
Os produtos cadastrados são salvos no arquivo `produtos.txt` para persistência dos dados.

---

## 📁 Estrutura do Projeto
  sistemaGerenciamentoProduto.c
  sistemaGerenciamentoProduto.exe
  .vscode/
  ├── c_cpp_properties.json
  ├── launch.json
  └── settings.json
  output/
  └── sistemaGerenciamentoProduto.exe

  - O código-fonte principal está em `sistemaGerenciamentoProduto.c`.  
  - O arquivo `produtos.txt` é gerado automaticamente para armazenar os produtos cadastrados.

---

## 📝 Observações Técnicas
- O sistema utiliza structs para representar produtos, itens do carrinho e o próprio carrinho.

- O gerenciamento de memória é feito dinamicamente com malloc e realloc.

- O menu é interativo e utiliza comandos do terminal para navegação.

- O arquivo de produtos é sobrescrito a cada alteração no cadastro.

## 🎓 Sobre a Tarefa
Este projeto foi desenvolvido como parte das atividades da disciplina de programação na Universidade Veiga de Almeida.

