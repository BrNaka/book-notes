<div align="center">
  <h1> Docker in Action </h1>
  <p> <i> Jeff Nickoloff</i> </p>
</div>

<div align='center'> 
  <img src="./images/capa.png" width="600px"> 
</div>

## Commands
- Basic
    - *docker run*: Pull an image and automatically start a container.
    - *docker run -it*: Starts a container in interactive mode with an open TTY.
    - *docker run -it --rm*: Remove a container after stop it.

- Volumes
    - *docker run -d --volumes-from ... --name ... [image]*: Volume container. 
    - *docker run --name bmweb -v ~/example-docs:/usr/local/apache2/htdocs -p 80:80 httpd:latest*: Bind mount volumes.
    - *docker run --name bmweb_ro -v ~/example-docks:/usr/local/apache2/htdocs:ro -p 80:80 httpd:latest*: Read-only bind mount volumes.
      
### Chapter 1 - Welcome to Docker
### Chapter 2 - Running software in containers
### Chapter 3 - Software installation simplified
### Chapter 4 - Persistente storage and shared state with volumes
- *A volume is a mount point on the container's directory tree where a portion of the host directoyr tree has been mounted.*
    - Volumes provide container-independent data management
    - Images are appropriate for packaging and distributing relatively static files like programs; Volumes hold dynamic data or specializations.
- *Volume containers*: Advanced pattern.
- *Bind mount volumes*: A bind volume is a volume that points to a user-specified location on the host file system. I'ts useful if you want to share data with other processes running outside a container.
    - Read-only bind mount volumes: Prevent any process inside the container from modifying the content of the volume.
- *Docker-managed volumes*: Docker daemon creates managed volumes in a portion of the host's file system that's owned by Docker.
- *Sharing volumes*
    - - There are two ways to share volumes between containers: Host-dependent sharing (Different container shared the same mount point) and Generalized sharing.
- Cleaning up managed volumes is a manual task. This default functionality prevents accidental destruction of potentially valuable data.
    - A volume can be orphan (delete a container without the -v option). Removing orphaned volumes requires messy manual steps.
    - I'ts a better idea to avoid the situation by getting nto the habit of using the -v option and uing the volume container pattern.
    - Orphan volumes render disk space unusable until you've cleaned them up.

### Chapter 5 - Network exposure
- Docker creates a virtual network that connects all of the running containers to the network that the computer is connected to. That network is called a *bridge*.
- Docker is concerned with two types of networking: single-host virtual network and multi-host networks.
    - *Local virtual networks*: I's used to provide container isolation.
    - *Multi-host virtual networks*: It provides an overlay where any container on a participating host can have its own routable IP address from any other container in the network.
- Docker bridge interface is called *docker0*.
- Container (Own IP Address) --> Container virtual interface --> docker0 interface --> Logical host interface --> Physical network interface.
- Four archtypes for network containers: Defines how a container interacts with other local containers and the host's network.
    - Closed: It doesn't allow any network traffic. It does not have a connection to the Docker bridge interface.
    - Bridged: It's the most customizable and should be hardened as a best practice. It's the most common network container archetype.
        - '--hostname' flag adds an entry to the DNS override system inside the container.
        - Bridged containers are not accessible from the host network by default. Containers are protected by your host's firewall system.
    - Joined: 
    - Open:
