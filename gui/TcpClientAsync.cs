using System;
using System.Net.Sockets;
using System.Text;
using System.Reflection;
using UnityEngine;
using System.Threading;

public class TcpClientAsync
{
    private TcpClient client = null;
    private string returndata = String.Empty;
    public bool connectStatus = false;
    public bool receiveStatus = false;
    public bool sendStatus = false;
    public bool disconnectStatus = false;
    public const int BufferSize = 4096;
    private byte[] buffer = new byte[BufferSize];
    private string sendMsg = String.Empty;
    private int port;
    private string ip;

    // Constructor
    public TcpClientAsync()
    {
        client = new TcpClient();
    }

    public void Connect(string _ip, int _port)
    {
        try
        {
            ip = _ip;
            port = _port;
            connectStatus = false;
            if (client.Connected)
                Disconnect();
            client.Client.BeginConnect(ip, port, new AsyncCallback(ConnectCallback), null);
        }
        catch (Exception e)
        {
            Console.WriteLine(e.ToString());
        }
    }

    public void ConnectCallback(IAsyncResult ar)
    {
        client.EndConnect(ar);
        client.Client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, 1);
        connectStatus = true;
    }

    public void Receive()
    {
        try
        {
            if (client.Connected)
            {
                returndata = String.Empty;
                receiveStatus = false;
                buffer = new byte[BufferSize];
                client.Client.BeginReceive(buffer, 0, BufferSize, SocketFlags.None, new AsyncCallback(ReceiveCallback), null);
            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e.ToString());
        }
    }

    private void ReceiveCallback(IAsyncResult ar)
    {
        int bytesRead = client.GetStream().EndRead(ar);
        if (bytesRead > 0)
        {
            returndata += Encoding.ASCII.GetString(buffer, 0, bytesRead);
            buffer = new byte[BufferSize];
            if (client.Client.Poll(0, SelectMode.SelectRead) || returndata[returndata.Length - 1] != '\n')
                client.Client.BeginReceive(buffer, 0, BufferSize, SocketFlags.None, new AsyncCallback(ReceiveCallback), null);
            else
            {
                receiveStatus = true;
            }
        }
        else
        {
            if (returndata.Length > 1)
                returndata += Encoding.ASCII.GetString(buffer, 0, bytesRead);
            receiveStatus = true;
            Disconnect();
        }
    }

    public void Send(string data)
    {
        if (client.Connected)
        {
            byte[] byteData = Encoding.ASCII.GetBytes(data);
            sendStatus = false;
            client.Client.BeginSend(byteData, 0, byteData.Length, 0, new AsyncCallback(SendCallback), null);
            sendMsg = data;
        }
    }

    private void SendCallback(IAsyncResult ar)
    {
        try
        {
            int bytesSent = client.Client.EndSend(ar);
            sendStatus = true;
        }
        catch (Exception e)
        {
            Console.WriteLine(e.ToString());
        }
    }

    public void Disconnect()
    {
        Thread.Sleep(2000);
        if (client.Connected)
        {
            client.GetStream().Close();
            client.Close();
            connectStatus = false;
            receiveStatus = false;
            sendStatus = false;
        }
    }

    public string getData()
    {
        return returndata;
    }

    public string getSend()
    {
        return sendMsg;
    }

    public string IP()
    {
        return ip;
    }

    public int Port()
    {
        return port;
    }

    public Socket getSocket()
    {
        return client.Client;
    }
}
