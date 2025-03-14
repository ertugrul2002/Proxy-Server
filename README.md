# HTTP Proxy Server (Client Side)

A simple HTTP Proxy Server implemented in C to handle GET requests, cache responses, and display content. This project was developed as a third-year assignment to explore socket programming and HTTP protocol basics.

## Key Features
- **HTTP GET Requests**: Constructs and sends HTTP GET requests to external servers.
- **Content Caching**: Saves responses (e.g., web pages, images, PDFs) in a local filesystem with directory structure matching the URL.
- **Socket Programming**: Uses TCP sockets to communicate with HTTP servers.
- **File Handling**: Organizes cached files locally.
- **Browser Support**: Optionally opens cached files in a browser using the `-s` flag.
- **Error Handling**: Manages errors like 404 Not Found and DNS resolution failures.

## How to Run
1. **Compile**: `gcc -Wall -o cproxy cproxy.c`
2. **Run**: `./cproxy <URL> [-s]`
   - Example: `./cproxy http://www.josephwcarrillo.com/JosephWhitfieldCarrillo.jpg`
   - Example with browser: `./cproxy http://www.josephwcarrillo.com/JosephWhitfieldCarrillo.jpg -s`

## Usage Examples
### Fetching a New File
When fetching a new file, the proxy constructs an HTTP request, sends it to the server, receives the response, and caches it locally.

![Screenshot from 2025-03-14 20-06-53](https://github.com/user-attachments/assets/89e228ce-3c37-4526-9601-db3cc032d503)

![Screenshot from 2025-03-14 20-07-35](https://github.com/user-attachments/assets/5071645c-87ed-4eb0-8389-601de985176b)

![Screenshot from 2025-03-14 20-08-00](https://github.com/user-attachments/assets/36108ede-54b2-46f8-9abd-9edcd12d7924)

![Screenshot from 2025-03-14 20-08-50](https://github.com/user-attachments/assets/32e870c1-f296-44a6-943d-d2feced35f70)

![Screenshot from 2025-03-14 20-09-03](https://github.com/user-attachments/assets/522b9716-4cf2-47c5-9c9c-7c75ae714756)

![Screenshot from 2025-03-15 00-05-44](https://github.com/user-attachments/assets/b1b42a11-5a84-48c5-a5ee-f6f919da13f2)

![Screenshot from 2025-03-15 00-05-59](https://github.com/user-attachments/assets/abd96337-9c10-47b9-8af1-faed352696d5)


### Fetching a PDF File
The proxy can fetch and cache PDF files, saving them locally in the corresponding directory structure.
![Screenshot from 2025-03-15 00-09-07](https://github.com/user-attachments/assets/3c70a8e7-5d4a-4696-95c8-56614349232b)
![Screenshot from 2025-03-15 00-09-18](https://github.com/user-attachments/assets/4ec25350-ac80-4ab9-bd08-e3c6bd09a91c)
![Screenshot from 2025-03-15 00-09-28](https://github.com/user-attachments/assets/fe36e73f-6bcc-47af-879d-abe9995b5eb1)
![Screenshot from 2025-03-15 00-09-43](https://github.com/user-attachments/assets/caf75a02-3552-4930-b96b-ef670324733d)
![Screenshot from 2025-03-15 00-09-55](https://github.com/user-attachments/assets/07be582e-bb3b-498b-a355-d65503b2c39d)
![Screenshot from 2025-03-15 00-10-21](https://github.com/user-attachments/assets/6c587206-873c-4eda-b340-2281140c6d40)


### Serving from Cache
When the requested file is already cached, the proxy serves it directly from the local filesystem.

![Screenshot_from_2025-03-15_00-26-02](https://github.com/user-attachments/assets/f7fb8475-9d33-4ee1-84cc-3e4bf0f007a3)



### Handling Errors
The proxy handles errors such as DNS resolution failures (e.g., invalid domain) or 404 Not Found responses.

![Screenshot from 2025-03-15 00-07-03](https://github.com/user-attachments/assets/63bc9714-8a12-4b24-aead-335c25750c8b)

![Screenshot from 2025-03-15 00-09-07](https://github.com/user-attachments/assets/bb5e60e1-ab27-478c-8c48-3ba1bd08f16c)



## Notes
- Developed as a third-year project to explore networking and HTTP.
- Designed to handle one request per execution and close the connection afterward, as per assignment requirements. This may cause issues when used as a browser proxy since browsers send multiple requests.
- Successfully tested with terminal-based requests and various URLs (e.g., `www.josephwcarrillo.com`, `example.com`, `www.pdf995.com`).
- Only supports HTTP (not HTTPS) and IPv4 connections.

## Future Improvements
- Modify the proxy to support multiple requests and Keep-Alive connections for better browser compatibility.
- Add support for HTTPS requests.
- Implement multithreading to handle multiple clients simultaneously.

- 
