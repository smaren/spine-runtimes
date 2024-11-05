import SwiftUI
import Spine

struct Physics: View {
    
    @StateObject
    var model = PhysicsModel()
    
    var body: some View {
		ZStack {
			Color(red: 51 / 255, green: 51 / 255, blue: 51 / 255).ignoresSafeArea()
			SpineView(
				from: .bundle(atlasFileName: "celestial-circus-pma.atlas", skeletonFileName: "celestial-circus-pro.skel"),
				controller: model.controller
			)
			.gesture(
				DragGesture(minimumDistance: 0)
					.onChanged { gesture in
						model.updateBonePosition(position: gesture.location)
					}
			)
		}
        .navigationTitle("Physics (drag anywhere)")
        .navigationBarTitleDisplayMode(.inline)
    }
}

#Preview {
    Physics()
}

final class PhysicsModel: ObservableObject {
    
    @Published
    var controller: SpineController!
    
    @Published
    var mousePosition: CGPoint?
    
    @Published
    var lastMousePosition: CGPoint?
    
    init() {
        controller = SpineController(
            onInitialized: { controller in
                controller.animationState.setAnimationByName(
                    trackIndex: 0,
                    animationName: "eyeblink",
                    loop: true
                )
                controller.animationState.setAnimationByName(
                    trackIndex: 1,
                    animationName: "wings-and-feet",
                    loop: true
                )
            },
            onAfterUpdateWorldTransforms: {
                [weak self] controller in guard let self else { return }
                
                guard let lastMousePosition else {
                    self.lastMousePosition = mousePosition
                    return
                }
                guard let mousePosition else {
                    return
                }
                let dx = mousePosition.x - lastMousePosition.x
                let dy = mousePosition.y - lastMousePosition.y
                let positionX = controller.skeleton.x + Float(dx)
                let positionY = controller.skeleton.y + Float(dy)
                controller.skeleton.setPosition(x: positionX, y: positionY)
                self.lastMousePosition = mousePosition
            }
        )
    }
    
    func updateBonePosition(position: CGPoint) {
        mousePosition = controller.toSkeletonCoordinates(position: position)
    }
}