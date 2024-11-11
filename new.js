const controls = new THREE.OrbitControls(camera, renderer.domElement);
controls.update();
gltf.scene.scale.set(0.5, 0.5, 0.5); // Adjust as needed
