# Stage 1: Clonar y construir Qt 6
FROM --platform=linux/amd64 ubuntu:22.04 AS qt6-build

# Instalar dependencias de construcción
RUN apt-get update && apt-get install -yqq \
    build-essential cmake ninja-build gcc g++ \
    curl libgl1-mesa-dev libxkbcommon-dev libfontconfig1-dev \
    python3 python3-pip && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Clonar el código fuente de Qt 6
RUN mkdir -p /opt/qt6-src && \
    curl -L https://download.qt.io/official_releases/qt/6.5/6.5.3/single/qt-everywhere-src-6.5.3.tar.xz | tar -xJ -C /opt/qt6-src --strip-components=1

# Configurar y compilar Qt 6
WORKDIR /opt/qt6-src
RUN mkdir -p /opt/qt6-build && cd /opt/qt6-build && \
    cmake /opt/qt6-src \
        -GNinja \
        -DCMAKE_BUILD_TYPE=Release \
        -DQT_BUILD_EXAMPLES=OFF \
        -DQT_FEATURE_opengl=ON \
        -DQT_FEATURE_vulkan=OFF \
        -DCMAKE_INSTALL_PREFIX=/opt/qt6 && \
    cmake --build . && \
    cmake --install .

# Stage 2: Contenedor DevContainer con Qt integrado
FROM --platform=linux/amd64 ubuntu:22.04

# Configurar entorno y dependencias básicas
RUN apt-get update && apt-get install -yqq \
        build-essential cmake gcc g++ gdb \
        curl libssl-dev python3 python3-pip \
        buildah openssh-client bridge-utils \
        net-tools inetutils-ping qemu-system-aarch64 \
        qemu-system-x86 bridge-utils iproute2 dnsmasq && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Configurar pip y Conan
RUN pip3 install --upgrade pip && pip3 install "conan>=2.0"

# Configurar directorios y entorno para QNX SDK
RUN mkdir -p /opt/qnx-sdk
ENV QNX_SDP_HOME=/opt/qnx-800-raspberrypi4b
ENV QNX_HOST=${QNX_SDP_HOME}/host/linux/x86_64
ENV QNX_TARGET=${QNX_SDP_HOME}/target/qnx8
ENV PATH=${QNX_HOST}/usr/bin:${PATH}
ENV PATH=${QNX_TARGET}/usr/bin:${PATH}

# Configuración de herramientas de compilación para QNX
ENV CC=qcc
ENV CXX=q++
ENV CPP=cpp
ENV LD=ld
ENV AR=ar
ENV NM=nm
ENV OBJCOPY=objcopy
ENV OBJDUMP=objdump
ENV RANLIB=ranlib
ENV READELF=readelf
ENV SIZE=size
ENV STRIP=strip

# Añadir configuración de entorno a bashrc
RUN echo 'source ${QNX_SDP_HOME}/qnxsdp-env.sh' >> /root/.bashrc

# Establecer directorio de trabajo
WORKDIR /workspaces

# Copiar Qt 6 desde el stage de compilación
COPY --from=qt6-build /opt/qt6 /opt/qt6

# Configurar perfiles de Conan para QNX
RUN mkdir -p /root/.conan2/profiles
COPY .devcontainer/conan_profiles /root/.conan2/profiles

# Configurar entorno de Qt 6 en el contenedor
ENV CMAKE_PREFIX_PATH=/opt/qt6
ENV PATH=/opt/qt6/bin:${PATH}

# Copiar docker_entrypoint.sh
COPY .devcontainer/docker_entrypoint.sh /usr/local/bin/docker_entrypoint.sh
RUN chmod +x /usr/local/bin/docker_entrypoint.sh

# Copiar la licencia de QNX
COPY .devcontainer/.qnx /root/.qnx

# Comando por defecto para systemd
ENTRYPOINT ["/usr/local/bin/docker_entrypoint.sh"]